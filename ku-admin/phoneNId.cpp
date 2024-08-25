#include "sqlite/sqlite3.h"
#include <iostream>

int executeSQL(sqlite3* db, const std::string& sql) {
    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        exit(EXIT_FAILURE); // Terminate the program on error
    }
    return rc;
}

// Function to check if Gmail already exists in the combined table
bool gmailExists(sqlite3* db, const std::string& gmail) {
    std::string checkSQL = "SELECT COUNT(*) FROM phoneNId WHERE gmail = '" + gmail + "';";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, 0);
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count > 0;
}

// Function to combine data from two databases into a new one
void combineDatabases(const std::string& db1Path, const std::string& db2Path) {
    sqlite3 *db1, *db2;
    sqlite3_open(db1Path.c_str(), &db1);
    sqlite3_open(db2Path.c_str(), &db2);

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS phoneNId ("
                                 "gmail TEXT PRIMARY KEY, "
                                 "studentId INTEGER, "
                                 "phoneNumber TEXT);";
    executeSQL(db1, createTableSQL);

    // Read from the first database
    std::string selectDb1SQL = "SELECT email, id FROM studentID;";
    sqlite3_stmt* stmt1;
    sqlite3_prepare_v2(db1, selectDb1SQL.c_str(), -1, &stmt1, 0);

    while (sqlite3_step(stmt1) == SQLITE_ROW) {
        std::string gmail = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 0));
        int studentId = sqlite3_column_int(stmt1, 1);

        // Check if Gmail already exists in the new table
        if (gmailExists(db1, gmail)) {
            std::cout << "Gmail " << gmail << " already exists in the new database." << std::endl;
            continue;
        }

        // Read the corresponding phoneNumber from the second database
        std::string selectDb2SQL = "SELECT mobile_number FROM Users WHERE gmail = '" + gmail + "';";
        sqlite3_stmt* stmt2;
        sqlite3_prepare_v2(db2, selectDb2SQL.c_str(), -1, &stmt2, 0);

        if (sqlite3_step(stmt2) == SQLITE_ROW) {
            std::string phoneNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 0));

            // Insert combined data into the new database
            std::string insertSQL = "INSERT INTO phoneNId (gmail, studentId, phoneNumber) VALUES ('" +
                                    gmail + "', " + std::to_string(studentId) + ", '" + phoneNumber + "');";
            executeSQL(db1, insertSQL);
        }
        sqlite3_finalize(stmt2);
    }
    sqlite3_finalize(stmt1);

    sqlite3_close(db1);
    sqlite3_close(db2);
}
