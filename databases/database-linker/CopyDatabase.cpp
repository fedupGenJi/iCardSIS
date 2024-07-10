#include "CopyDatabase.hpp"
#include <iostream>

CopyDatabase::CopyDatabase(const std::string& dbPath) : db(nullptr) {
    openDatabase(dbPath);
    std::cout << "Opened database: " << dbPath << std::endl;
}

CopyDatabase::~CopyDatabase() {
    closeDatabase();
}

void CopyDatabase::openDatabase(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }
}

void CopyDatabase::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Closed database." << std::endl;
    }
}

std::vector<int> CopyDatabase::getIDs(const std::string& tableName) {
    std::vector<int> ids;
    std::string sql = "SELECT id FROM " + tableName + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return ids;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ids.push_back(sqlite3_column_int(stmt, 0));
    }
    sqlite3_finalize(stmt);
    return ids;
}

void CopyDatabase::insertIDs(const std::string& tableName, const std::vector<int>& ids) {
    for (int id : ids) {
        // Check if the ID already exists in the target table
        std::string checkSql = "SELECT COUNT(*) FROM " + tableName + " WHERE studentID = ?;";
        sqlite3_stmt* checkStmt;
        int rc = sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            continue; // Skip to next ID on error
        }
        sqlite3_bind_int(checkStmt, 1, id);
        rc = sqlite3_step(checkStmt);
        bool idExists = (rc == SQLITE_ROW && sqlite3_column_int(checkStmt, 0) > 0);
        sqlite3_finalize(checkStmt);

        if (idExists) {
            std::cout << "ID " << id << " already exists in " << tableName << ". Skipping." << std::endl;
            continue; // Skip inserting this ID
        }

        // Insert the ID if it doesn't already exist
        std::string sql = "INSERT INTO " + tableName + " (studentID) VALUES (?);";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            continue; // Skip to next ID on error
        }
        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "ID " << id << " inserted successfully into " << tableName << "." << std::endl;
        }
        sqlite3_finalize(stmt);
    }
}

void CopyDatabase::displayTable(const std::string& tableName) {
    std::string sql = "SELECT * FROM " + tableName + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    int cols = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int col = 0; col < cols; col++) {
            std::cout << sqlite3_column_text(stmt, col) << " ";
        }
        std::cout << std::endl;
    }
    sqlite3_finalize(stmt);
}