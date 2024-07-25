#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

bool checkStudentIdExists(sqlite3* DB, int studentId) {
    std::string sql = "SELECT COUNT(*) FROM Student WHERE studentId = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    rc = sqlite3_step(stmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count > 0;
}

int main() {
    sqlite3* DB;
    int exit = sqlite3_open("balance.db", &DB);

    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    } else {
        std::cout << "Opened Database Successfully!" << std::endl;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Student ("
                      "studentId INTEGER PRIMARY KEY, "
                      "balance INTEGER DEFAULT 0);";

    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }

    int studentId;
    std::cout << "Enter student ID: ";
    std::cin >> studentId;

    if (checkStudentIdExists(DB, studentId)) {
        std::cout << "Student ID " << studentId << " exists in the database." << std::endl;
    } else {
        std::cout << "Student ID " << studentId << " does not exist in the database." << std::endl;
    }

    sqlite3_close(DB);
    return 0;
}