#include "include/busSubscription.h"
#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
using namespace std;

void checkForTable(sqlite3* db, int studentId) {
    char* errMsg = 0;
    int rc;

    if (!db) {
        std::cerr << "Invalid database connection." << std::endl;
        return;
    }

    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Transportation(
            studentId INT PRIMARY KEY NOT NULL,
            status TEXT ,
            routePlace TEXT ,
            deadline TEXT ,
            daysLeft INT 
        );
    )";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    } else {
        std::cout << "Table created successfully or already exists\n";
    }

    // Check if studentId exists
    sqlite3_stmt* stmt;
    const char* checkStudentSQL = "SELECT COUNT(*) FROM Transportation WHERE StudentId = ?;";

    rc = sqlite3_prepare_v2(db, checkStudentSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 0) {
            std::cerr << "Error: Student ID " << studentId << " does not exist in the Transportation table." << std::endl;
        } else {
            std::cout << "Student ID " << studentId << " exists in the Transportation table." << std::endl;
        }
    }

    sqlite3_finalize(stmt);
}

void bus_Subscription(sqlite3 *db, int studentId) {
    checkForTable(db,studentId);
}