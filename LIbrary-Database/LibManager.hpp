#ifndef LIBMANAGER_HPP
#define LIBMANAGER_HPP

#include "sqlite/sqlite3.h"
#include <string>

class LibManager {
public:
    LibManager(const std::string& dbPath);
    ~LibManager();

    bool checkBorrower(int studentID);
    void addBook(int studentID, const std::string& bookID, const std::string& bookName, const std::string& submissionDate);
    void removeBook(int studentID, const std::string& bookID);

private:
    sqlite3* db;

    void initializeDatabase();
    void closeDatabase();
    std::string calculateDeadline(const std::string& submissionDate);
};

#endif // LIBMANAGER_HPP
