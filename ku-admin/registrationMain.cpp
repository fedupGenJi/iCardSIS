#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include <QMessageBox>

void Errormssg(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
void Successmssg(const QString &message){
    QMessageBox::information(nullptr,"Sucess!",message);
}

// Function to check if a Gmail exists in the Users table
bool doesGmailExist(const std::string& gmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_open("A:\\iCardSIS\\databases\\login-database\\registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT COUNT(*) FROM Users WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                exists = sqlite3_column_int(stmt, 0) > 0;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
            Errormssg("ERROR!");
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        Errormssg("ERROR!");
    }
    return exists;
}

// Function to remove a user by Gmail
bool removeUserByGmail(const std::string& gmail) {
    if (!doesGmailExist(gmail)) {
        std::cout << "The Gmail address does not exist in the database.\n";
        Errormssg("Gmail doesnot exist in the database.");
        return false;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_open("A:\\iCardSIS\\databases\\login-database\\registration.db", &db) == SQLITE_OK) {
        const char* sql = "DELETE FROM Users WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, gmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "User with Gmail " << gmail << " removed successfully.\n";
                Successmssg("User removed!");
                success = true;
            } else {
                std::cerr << "Error during removal: " << sqlite3_errmsg(db) << "\n";
                Errormssg("ERROR!");
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
            Errormssg("ERROR!");
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        Errormssg("ERROR!");
    }
    return success;
}

// Function to change the phone number of a user
bool changePhoneNumber(const std::string& gmail, const std::string& new_phone_number) {
    if (!doesGmailExist(gmail)) {
        std::cout << "The Gmail address does not exist in the database.\n";
        Errormssg("Gmail doesn't exist in the database.");
        return false;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_open("A:\\iCardSIS\\databases\\login-database\\registration.db", &db) == SQLITE_OK) {
        const char* sql = "UPDATE Users SET mobile_number = ? WHERE gmail = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, new_phone_number.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, gmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "Phone number for user with Gmail " << gmail << " updated successfully.\n";
                Successmssg("Phone Number updated Successfully!");
                success = true;
            } else {
                std::cerr << "Error during update: " << sqlite3_errmsg(db) << "\n";
                Errormssg("ERROR!");
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
            Errormssg("ERROR!");
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        Errormssg("ERROR!");
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
                Successmssg("User Removed!");
                success = true;
            } else {
                std::cerr << "Error during removal from phoneNId table: " << sqlite3_errmsg(db) << "\n";
                Errormssg("ERROR!");
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement for phoneNId table: " << sqlite3_errmsg(db) << "\n";
            Errormssg("ERROR!");
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        Errormssg("ERROR!");
    }

    return success;
}
