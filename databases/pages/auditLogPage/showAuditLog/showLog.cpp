#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>
#include "showLog.h"
void showLog(int studentId) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::string dbName = "A:/iCardSIS/databases/pages/auditLogPage/auditLog.db"; // Replace with your database name
    std::string tableName = "Student_" + std::to_string(studentId);
    std::string query = "SELECT * FROM " + tableName;

    // Open the database
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Execute the query and display the table
    std::cout << "Table " << tableName << ":\n";
    int colCount = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int col = 0; col < colCount; col++) {
            std::cout << sqlite3_column_text(stmt, col) << " ";
        }
        std::cout << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}