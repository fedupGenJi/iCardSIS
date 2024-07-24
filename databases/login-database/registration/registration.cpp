#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>

// Function to create the Users table if it doesn't exist
void createUsersTable() {
    sqlite3* db;
    char* errMessage = nullptr;
    int rc;

    rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        return;
    } else {
        std::cout << "Opened database successfully.\n";
    }

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            mobile_number TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL,
            gmail TEXT NOT NULL UNIQUE
        );
    )";

    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to create table: " << errMessage << "\n";
        sqlite3_free(errMessage);
    } else {
        std::cout << "Users table is ready.\n";
    }

    sqlite3_close(db);
}

// Function to check if a Gmail is valid
bool isGmailValid(const std::string& gmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool valid = false;

    if (sqlite3_open("A:\\iCardSIS\\databases\\ku-database\\example.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT COUNT(*) FROM studentId WHERE email = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                valid = sqlite3_column_int(stmt, 0) > 0;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return valid;
}

// Function to check if a Gmail is already registered
bool isGmailRegistered(const std::string& gmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool registered = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT COUNT(*) FROM Users WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                registered = sqlite3_column_int(stmt, 0) > 0;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return registered;
}

// Function to check if a phone number is already registered
bool isPhoneNumberRegistered(const std::string& mobile_number) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool registered = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT COUNT(*) FROM Users WHERE mobile_number = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, mobile_number.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                registered = sqlite3_column_int(stmt, 0) > 0;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return registered;
}

//function to generate a encryption
std::string generatecrypt(std::string data)
{
    unsigned int result(0);

    for(unsigned int ch : data)
    result=ch + (result<<4) + (result<<10) - result;

    return std::to_string(result);
}

// Function to register a user
bool registerUser(const std::string& mobile_number, const std::string& password, const std::string& confirm_password, const std::string& gmail) {
    if (!isGmailValid(gmail)) {
        std::cout << "The Gmail address is not present in the KU-Database.\n";
        return false;
    }

    if (isGmailRegistered(gmail)) {
        std::cout << "The Gmail address is already registered.\n";
        return false;
    }

    if (isPhoneNumberRegistered(mobile_number)) {
        std::cout << "The phone number is already registered.\n";
        return false;
    }

    if (password != confirm_password) {
        std::cout << "The passwords do not match.\n";
        return false;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;

    //encrypt
    std::string hashedPassword = generatecrypt(password);

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "INSERT INTO Users (mobile_number, password, gmail) VALUES (?, ?, ?)";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, mobile_number.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, gmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "Registration successful!\n";
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return true;
            } else {
                std::cout << "Error during registration: " << sqlite3_errmsg(db) << "\n";
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }

    return false;
}

int main() {
    // Create the Users table if it doesn't exist
    createUsersTable();

    std::string mobile_number, password, confirm_password, gmail;
    
    std::cout << "Enter your mobile number: ";
    std::getline(std::cin, mobile_number);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    std::cout << "Confirm your password: ";
    std::getline(std::cin, confirm_password);
    std::cout << "Enter your Gmail address: ";
    std::getline(std::cin, gmail);

    registerUser(mobile_number, password, confirm_password, gmail);

    return 0;
}