#ifndef COPYDATABASE_HPP
#define COPYDATABASE_HPP

#include "sqlite/sqlite3.h"
#include <string>
#include <vector>

class CopyDatabase {
public:
    CopyDatabase(const std::string& dbPath);
    ~CopyDatabase();

    std::vector<int> getIDs(const std::string& tableName);
    void insertIDs(const std::string& tableName, const std::vector<int>& ids);
    void displayTable(const std::string& tableName);


private:
    sqlite3* db;

    void openDatabase(const std::string& dbPath);
    void closeDatabase();
};

#endif // COPYDATABASE_HPP
