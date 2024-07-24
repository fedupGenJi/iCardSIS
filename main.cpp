#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

// Function to open or create the SQLite database
sqlite3* openDatabase(const std::string& dbName) {
    sqlite3* db;
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return db;
}

//function to generate a encryption
std::string generatecrypt(std::string& data)
{
    unsigned int result(0);

    for(unsigned int ch : data)
    result=ch + (result<<4) + (result<<10) - result;

    return std::to_string(result);
}

// Function to execute a SQL statement
bool executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int main() {
    // Database file name
    const std::string dbName = "users.db";
    
    // Open or create the SQLite database
    sqlite3* db = openDatabase(dbName);
    if (!db) return 1;

    // Create table if it doesn't exist
    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Users (PhoneNumber TEXT PRIMARY KEY, HashedPassword TEXT NOT NULL);";
    if (!executeSQL(db, createTableSQL)) return 1;

    // Get user input
    std::string phoneNumber;
    std::string password;
    
    std::cout << "Enter your phone number: ";
    std::getline(std::cin, phoneNumber);
    
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    // Hash the password
    std::string hashedPassword = generatecrypt(password);

    // Insert the user data into the database
    std::string insertSQL = "INSERT INTO Users (PhoneNumber, HashedPassword) VALUES ('" + phoneNumber + "', '" + hashedPassword + "');";
    if (!executeSQL(db, insertSQL)) return 1;

    std::cout << "User data saved successfully!" << std::endl;

    // Close the database
    sqlite3_close(db);

    return 0;
}
