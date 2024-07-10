#ifndef LIBMANAGER_HPP
#define LIBMANAGER_HPP

#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>

class LibManager {
public:
    LibManager(const std::string& dbPath);
    ~LibManager();

    bool checkStudentID(int studentID);
    void addBook(int studentID, const std::string& bookID, const std::string& bookName);
    void removeBook(int studentID, const std::string& bookID);

private:
    sqlite3* db;

    void initializeDatabase();
    void closeDatabase();
};

#endif // LIBMANAGER_HPP