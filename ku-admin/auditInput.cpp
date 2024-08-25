#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "auditInput.h"


std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d");
    return oss.str();
}

void insertActivity(int studentId, const std::string& activity) {
    sqlite3* db;
    int rc = sqlite3_open("A:/iCardSIS/pages/auditLogPage/auditLog.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string tableName = "Student_" + std::to_string(studentId);

    std::string date = getCurrentDate();
    std::string insertSQL = "INSERT INTO " + tableName + " (date, activity) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, activity.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Activity inserted successfully for student " << studentId << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}