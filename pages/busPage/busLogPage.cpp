#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

void showBusLog(int studentId) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    
    rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string sql = "SELECT status, routePlace, daysLeft FROM Transportation WHERE studentId = ?";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        
        if (status == "INACTIVE") {
            std::cout << "Status: INACTIVE" << std::endl;
        } else if (status == "ACTIVE") {
            std::string routePlace = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int daysLeft = sqlite3_column_int(stmt, 2);

            std::cout << "Status: ACTIVE" << std::endl;
            std::cout << "Route Place: " << routePlace << std::endl;
            std::cout << "Days Left: " << daysLeft << std::endl;

            // Prepare the SQL query to get the imgpath from the studentId table
            sql = "SELECT imgpath FROM studentId WHERE id = ?";

            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                return;
            }

            // Bind the studentId to the SQL query
            sqlite3_bind_int(stmt, 1, studentId);

            // Execute the query
            rc = sqlite3_step(stmt);
            if (rc == SQLITE_ROW) {
                std::string imgpath = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::cout << "Image Path: " << imgpath << std::endl;
            } else {
                std::cerr << "No image path found for studentId: " << studentId << std::endl;
            }
        } else {
            std::cerr << "Unexpected status value." << std::endl;
        }
    } else {
        std::cout << "No record found for studentId: " << studentId << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}