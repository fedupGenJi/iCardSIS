#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>

// Function to verify user login
bool verifyLogin(const std::string& mobile_number, const std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool login_successful = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT password FROM Users WHERE mobile_number = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, mobile_number.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string stored_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                if (password == stored_password) {
                    login_successful = true;
                } else {
                    std::cout << "Incorrect password.\n";
                }
            } else {
                std::cout << "Phone number not registered.\n";
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return login_successful;
}

int main() {
    std::string mobile_number, password;

    std::cout << "Enter your phone number: ";
    std::getline(std::cin, mobile_number);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    if (verifyLogin(mobile_number, password)) {
        std::cout << "Login successful!\n";
    } else {
        std::cout << "Login failed.\n";
    }

    return 0;
}