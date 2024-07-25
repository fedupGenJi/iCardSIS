#include <iostream>
#include "vendors/sqlite/sqlite3.h"

// Function to delete a table
void deleteTable(sqlite3* db, const std::string& tableName) {
    std::string sql = "DROP TABLE IF EXISTS " + tableName + ";";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table " << tableName << " deleted successfully.\n";
    }
}

int main() {
    sqlite3* db;
    const char* dbName = "databases/ku-database/ku-database.db";
    
    // Open the database
    int rc = sqlite3_open(dbName, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully.\n";
    }

    // Specify the table name to delete
    std::string tableName = "phoneNId";

    // Delete the specified table
    deleteTable(db, tableName);

    // Close the database
    sqlite3_close(db);

    return 0;
}