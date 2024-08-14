#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>

// Function to check if a Gmail exists in the Users table
bool doesGmailExist(const std::string& gmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT COUNT(*) FROM Users WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                exists = sqlite3_column_int(stmt, 0) > 0;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return exists;
}

// Function to remove a user by Gmail
bool removeUserByGmail(const std::string& gmail) {
    if (!doesGmailExist(gmail)) {
        std::cout << "The Gmail address does not exist in the database.\n";
        return false;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "DELETE FROM Users WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "User with Gmail " << gmail << " removed successfully.\n";
                success = true;
            } else {
                std::cerr << "Error during removal: " << sqlite3_errmsg(db) << "\n";
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return success;
}

// Function to change the phone number of a user
bool changePhoneNumber(const std::string& gmail, const std::string& new_phone_number) {
    if (!doesGmailExist(gmail)) {
        std::cout << "The Gmail address does not exist in the database.\n";
        return false;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_open("registration.db", &db) == SQLITE_OK) {
        const char* sql = "UPDATE Users SET mobile_number = ? WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, new_phone_number.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, gmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "Phone number for user with Gmail " << gmail << " updated successfully.\n";
                success = true;
            } else {
                std::cerr << "Error during update: " << sqlite3_errmsg(db) << "\n";
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }
    return success;
}

// Function to remove a Gmail from the phoneNId table
bool removeFromPhoneNIdTable(const std::string& gmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db) == SQLITE_OK) {
        const char* sql = "DELETE FROM phoneNId WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "User with Gmail " << gmail << " removed successfully from phoneNId table.\n";
                success = true;
            } else {
                std::cerr << "Error during removal from phoneNId table: " << sqlite3_errmsg(db) << "\n";
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement for phoneNId table: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
    }

    return success;
}

int main() {
    int choice;
    std::string gmail, new_phone_number;

    std::cout << "Choose an operation:\n";
    std::cout << "1. Remove a user by Gmail\n";
    std::cout << "2. Change phone number\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;
    std::cin.ignore(); // To ignore the newline character left in the buffer

    if (choice == 1) {
        std::cout << "Enter the Gmail address of the user to remove: ";
        std::getline(std::cin, gmail);
         if (removeUserByGmail(gmail)) {
            removeFromPhoneNIdTable(gmail);
        }
    } else if (choice == 2) {
        std::cout << "Enter the Gmail address of the user: ";
        std::getline(std::cin, gmail);
        std::cout << "Enter the new phone number: ";
        std::getline(std::cin, new_phone_number);
        if (changePhoneNumber(gmail, new_phone_number)) {
            removeFromPhoneNIdTable(gmail);
        }
    } else {
        std::cout << "Invalid choice.\n";
    }

    return 0;
}