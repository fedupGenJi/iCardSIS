#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>
#include "A:\iCardSIS\pages\firstPage\studentInfo.h"

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

//function to generate a encryption
std::string generatecrypt(std::string data)
{
    unsigned int result(0);

    for(unsigned int ch : data)
    result=ch + (result<<4) + (result<<10) - result;

    return std::to_string(result);
}

int getStudentIdFromPhoneNumber(const std::string& phoneNumber) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    int studentId = -1; // Default value indicating not found

    // Open the SQLite database
    rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return studentId;
    }

    // Prepare the SQL statement
    std::string sql = "SELECT studentId FROM phoneNId WHERE phoneNumber = ?";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return studentId;
    }

    // Bind the phone number to the statement
    rc = sqlite3_bind_text(stmt, 1, phoneNumber.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind phone number: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return studentId;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        studentId = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Database not updated. Phone number not found." << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return studentId;
}

int main() {
    std::string mobile_number, password;

    std::cout << "Enter your phone number: ";
    std::getline(std::cin, mobile_number);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    std::string hashedPassword = generatecrypt(password);

    if (verifyLogin(mobile_number, hashedPassword)) {
        std::cout << "Login successful!\n";
        
        int studentId = getStudentIdFromPhoneNumber(mobile_number);
    if (studentId != -1) {
        std::cout << "Student ID: " << studentId << std::endl;
        firstPage(studentId);
    } else {
        std::cout << "No student ID found for the given phone number." << std::endl;
    }
        
    } else {
        std::cout << "Login failed.\n";
    }

    return 0;
}