#include "LibManager.hpp"
#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

LibManager::LibManager(const std::string& dbPath) : db(nullptr) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }
    initializeDatabase();
}

LibManager::~LibManager() {
    closeDatabase();
}

void LibManager::initializeDatabase() {
    // Create necessary tables if they don't exist
    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS Books ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   studentID INTEGER,"
        "   bookID TEXT,"
        "   bookName TEXT"
        ");";

    char* errMsg = 0;
    if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void LibManager::closeDatabase() {
    sqlite3_close(db);
    std::cout << "Closed database." << std::endl;
}

bool LibManager::checkStudentID(int studentID) {
    std::string sql = "SELECT COUNT(*) FROM Books WHERE studentID = " + std::to_string(studentID) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return (result > 0);
}

void LibManager::addBook(int studentID, const std::string& bookID, const std::string& bookName) {
    std::string sql = "INSERT INTO Books (studentID, bookID, bookName) VALUES (" + std::to_string(studentID) + ", '" + bookID + "', '" + bookName + "');";
    char* errMsg = 0;
    if (sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Book added successfully." << std::endl;
    }
}

void LibManager::removeBook(int studentID, const std::string& bookID) {
    std::string sql = "DELETE FROM Books WHERE studentID = " + std::to_string(studentID) + " AND bookID = '" + bookID + "';";
    char* errMsg = 0;
    if (sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Book removed successfully." << std::endl;
    }
}