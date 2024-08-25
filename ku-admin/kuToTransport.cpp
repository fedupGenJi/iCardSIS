#include <iostream>
#include "sqlite/sqlite3.h"
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "auditInput.h"

std::string getCurrentTime() {
    // Get the current time
    std::time_t now = std::time(nullptr);

    // Convert it to local time
    std::tm* localTime = std::localtime(&now);

    // Format the time as a string
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return std::string(buffer);
}

std::tm parseDateTime(const std::string& dateTime) {
    std::tm tm = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return tm;
}

bool updateStatusAndDaysLeft(const std::vector<int>& ids, const std::string& dbPath) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string query = "SELECT status, deadline, daysLeft FROM Transportation WHERE studentId = ?";
    std::string updateDaysLeftQuery = "UPDATE Transportation SET daysLeft = ? WHERE studentId = ?";
    std::string updateStatusQuery = "UPDATE Transportation SET status = 'INACTIVE' WHERE studentId = ?";
    std::string clearColumnsQuery = "UPDATE Transportation SET daysLeft = 0, deadline = NULL, routePlace = NULL WHERE studentId = ?";

    for (int id : ids) {
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            const char* status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* deadline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int daysLeft = sqlite3_column_int(stmt, 2);

            if (std::string(status) == "ACTIVE") {
                // Get current date
                std::string currentTime = getCurrentTime();
                std::tm deadline_tm = parseDateTime(deadline);
                std::time_t deadline_time = std::mktime(&deadline_tm);

                std::tm now_tm = parseDateTime(currentTime);
                std::time_t now_time = std::mktime(&now_tm);

                double difference = std::difftime(deadline_time, now_time) / (60 * 60 * 24); // Difference in days

                if (difference > 0) {
                    // Update daysLeft
                    sqlite3_stmt* updateStmt;
                    rc = sqlite3_prepare_v2(db, updateDaysLeftQuery.c_str(), -1, &updateStmt, nullptr);
                    if (rc != SQLITE_OK) {
                        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
                        continue;
                    }

                    sqlite3_bind_int(updateStmt, 1, static_cast<int>(difference));
                    sqlite3_bind_int(updateStmt, 2, id);

                    rc = sqlite3_step(updateStmt);
                    if (rc != SQLITE_DONE) {
                        std::cerr << "Failed to update daysLeft: " << sqlite3_errmsg(db) << std::endl;
                    }

                    sqlite3_finalize(updateStmt);
                } else {
                    // Update status to INACTIVE
                    sqlite3_stmt* updateStmt;
                    rc = sqlite3_prepare_v2(db, updateStatusQuery.c_str(), -1, &updateStmt, nullptr);
                    if (rc != SQLITE_OK) {
                        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
                        continue;
                    }

                    sqlite3_bind_int(updateStmt, 1, id);

                    rc = sqlite3_step(updateStmt);
                    if (rc != SQLITE_DONE) {
                        std::cerr << "Failed to update status: " << sqlite3_errmsg(db) << std::endl;
                    }

                    sqlite3_finalize(updateStmt);

                    // Clear daysLeft, deadline, and route columns
                    rc = sqlite3_prepare_v2(db, clearColumnsQuery.c_str(), -1, &updateStmt, nullptr);
                    if (rc != SQLITE_OK) {
                        std::cerr << "Failed to prepare clear columns statement: " << sqlite3_errmsg(db) << std::endl;
                        continue;
                    }

                    sqlite3_bind_int(updateStmt, 1, id);

                    rc = sqlite3_step(updateStmt);
                    if (rc != SQLITE_DONE) {
                        std::cerr << "Failed to clear columns: " << sqlite3_errmsg(db) << std::endl;
                    }

                    sqlite3_finalize(updateStmt);

                    std::cout << "Bus Subscription expired for studentId: " << id << std::endl;
                    std::string textmsg = "Bus Subscription Expired.";
                    insertActivity(id,textmsg);
                }
            }
        } else if (rc != SQLITE_DONE) {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return true;
}
