#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <vector>
#include <string>

std::vector<int> getStudentIds(sqlite3* db);
void createStudentActivityTables(const std::vector<int>& studentIds);
bool tableExists(sqlite3* db, const std::string& tableName);

int main() {
    sqlite3* db;
    int rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    std::vector<int> studentIds = getStudentIds(db);
    sqlite3_close(db);

    createStudentActivityTables(studentIds);

    return 0;
}

std::vector<int> getStudentIds(sqlite3* db) {
    std::vector<int> studentIds;
    const char* sql = "SELECT id FROM studentId";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return studentIds;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        studentIds.push_back(sqlite3_column_int(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return studentIds;
}

bool tableExists(sqlite3* db, const std::string& tableName) {
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "'";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

void createStudentActivityTables(const std::vector<int>& studentIds) {
    sqlite3* db;
    int rc = sqlite3_open("A:/iCardSIS/pages/auditLogPage/auditLog.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    for (int studentId : studentIds) {
        std::string tableName = "Student_" + std::to_string(studentId);
        
        if (tableExists(db, tableName)) {
            std::cout << "Table " << tableName << " already exists. Skipping creation." << std::endl;
            continue;
        }

        std::string createTableSQL = "CREATE TABLE " + tableName + " (date TEXT, activity TEXT)";
        char* errMsg = nullptr;
        rc = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        } else {
            std::cout << "Table " << tableName << " created successfully." << std::endl;
        }
    }

    sqlite3_close(db);
}