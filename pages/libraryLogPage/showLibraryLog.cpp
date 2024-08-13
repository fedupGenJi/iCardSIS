#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include "showLibraryLog.h"

void showLibraryLog(int studentId) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Books WHERE studentID = ?";

    int rc = sqlite3_open("A:/iCardSIS/databases/library-database/library.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    std::cout << "Books borrowed by student ID " << studentId << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int studentID = sqlite3_column_int(stmt,1);
        const unsigned char* bookId = sqlite3_column_text(stmt,2);
        const unsigned char* bookName = sqlite3_column_text(stmt, 3);
        const unsigned char* borrowedDate = sqlite3_column_text(stmt, 4);
        const unsigned char* deadline = sqlite3_column_text(stmt, 5);
        int daysDued = sqlite3_column_int(stmt, 6);

        std::cout << "ID: " << id
                  << "\t Student Id:" << studentID
                  << "\t Book Id:" <<bookId
                  << "\t Book Name: " << bookName
                  << "\t Borrowed Date: " << borrowedDate
                  << "\t Deadline: " << deadline
                  << "\t Days Dued: " << daysDued << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}