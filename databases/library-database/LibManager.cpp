#include "LibManager.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "A:\iCardSIS\databases\pages\auditLogPage\auditInput.h"
// Constructor: Opens the database and initializes it
LibManager::LibManager(const std::string& dbPath) : db(nullptr) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }
    initializeDatabase();
}

// Destructor: Closes the database
LibManager::~LibManager() {
    closeDatabase();
}

// Initialize the database with Books and Borrowers tables
void LibManager::initializeDatabase() {
    const char* createBooksTableSQL =
        "CREATE TABLE IF NOT EXISTS Books ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   studentID INTEGER,"
        "   bookID TEXT,"
        "   bookName TEXT,"
        "   submissionDate TEXT,"
        "   deadline TEXT,"
        "   days_dued INTEGER DEFAULT 0"
        ");";

    const char* createBorrowersTableSQL =
        "CREATE TABLE IF NOT EXISTS Borrowers ("
        "   studentID INTEGER PRIMARY KEY,"
        "   fine INTEGER DEFAULT 0"
        ");";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, createBooksTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Books table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, createBorrowersTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Borrowers table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Close the database connection
void LibManager::closeDatabase() {
    if (db) {
        sqlite3_close(db);
    }
}

// Check if a borrower exists in the Borrowers table
bool LibManager::checkBorrower(int studentID) {
    const char* checkBorrowerSQL = "SELECT COUNT(*) FROM Borrowers WHERE studentID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkBorrowerSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, studentID);
    rc = sqlite3_step(stmt);
    bool exists = false;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);
    return exists;
}

// Calculate deadline as 30 days after submission date
std::string LibManager::calculateDeadline(const std::string& submissionDate) {
    struct tm tm = {};
    std::istringstream ss(submissionDate);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    tm.tm_mday += 30;
    mktime(&tm);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return std::string(buffer);
}

// Add a book record to the Books table
void LibManager::addBook(int studentID, const std::string& bookID, const std::string& bookName, const std::string& submissionDate) {
    std::string deadline = calculateDeadline(submissionDate);
    const char* insertSQL = "INSERT INTO Books (studentID, bookID, bookName, submissionDate, deadline) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, studentID);
    sqlite3_bind_text(stmt, 2, bookID.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, bookName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, submissionDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, deadline.c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_finalize(stmt);
    std :: string text = "Added " + bookName + " with Submission Date: " + submissionDate;
    insertActivity(studentID,text);
}

// Remove a book record from the Books table
void LibManager::removeBook(int studentID, const std::string& bookID) {
    // Check if the book exists for the given studentID
    const char* checkBookSQL = "SELECT COUNT(*) FROM Books WHERE studentID = ? AND bookID = ?";
    sqlite3_stmt* checkStmt;
    int rc = sqlite3_prepare_v2(db, checkBookSQL, -1, &checkStmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(checkStmt, 1, studentID);
    sqlite3_bind_text(checkStmt, 2, bookID.c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(checkStmt);
    bool exists = false;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(checkStmt, 0) > 0;
    }
    sqlite3_finalize(checkStmt);

    if (!exists) {
        std::cerr << "Error: No book with ID " << bookID << " found for student ID " << studentID << "." << std::endl;
        return;
    }
    //get the BookName
    const char* getBookNameSQL = "SELECT bookName FROM Books WHERE studentID = ? AND bookID = ?";
    sqlite3_stmt* getNameStmt;
    rc = sqlite3_prepare_v2(db, getBookNameSQL, -1, &getNameStmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(getNameStmt, 1, studentID);
    sqlite3_bind_text(getNameStmt, 2, bookID.c_str(), -1, SQLITE_TRANSIENT);
    std::string bookName;
    rc = sqlite3_step(getNameStmt);
    if (rc == SQLITE_ROW) {
        bookName = reinterpret_cast<const char*>(sqlite3_column_text(getNameStmt, 0));
    } else {
        std::cerr << "Error retrieving book name: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(getNameStmt);
        return;
    }
    sqlite3_finalize(getNameStmt);

    // Delete the book record if it exists
    const char* deleteSQL = "DELETE FROM Books WHERE studentID = ? AND bookID = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, studentID);
    sqlite3_bind_text(stmt, 2, bookID.c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error deleting data: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_finalize(stmt);




    
    std :: string text = "Removed " + bookName;
    insertActivity(studentID,text);
}