#include "include/databaseOperation.h"
#include <iostream>

using namespace std;

bool checkStudentId(sqlite3 *db, int studentId) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM phoneNId WHERE studentId = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count > 0;
}

double getBalance(sqlite3 *db, int studentId) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT balance FROM Balance WHERE studentId = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    double balance = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balance = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return balance;
}

bool updateBalance(sqlite3 *db, int studentId, int amount) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Balance SET balance = balance + ? WHERE studentId = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_int(stmt, 2, studentId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Failed to update balance: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
