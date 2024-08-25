#include "include/fineOperation.h"
#include "include/databaseOperation.h"
#include "A:\iCardSIS\pages\auditLogPage\auditInput.h"
#include <iostream>
#include <string>

using namespace std;

void payFines(sqlite3 *finesDb, sqlite3 *db, int studentId) {
    // Check current fine amount
    sqlite3_stmt *stmt;
    const char *sql = "SELECT fine FROM Borrowers WHERE studentID = ?";
    if (sqlite3_prepare_v2(finesDb, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(finesDb) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    int currentFine = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        currentFine = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (currentFine == 0) {
        cout << "No fine to pay!" << endl;
        return;
    }

    int fineAmount;
    cout << "Current fine amount: " << currentFine << endl;
    cout << "Enter fine amount to pay: ";
    cin >> fineAmount;

    int balance = getBalance(db, studentId);
    if (balance < fineAmount) {
        cerr << "Insufficient balance to pay the fine!" << endl;
        return;
    }

    sql = "UPDATE Borrowers SET fine = fine - ? WHERE studentID = ?";
    if (sqlite3_prepare_v2(finesDb, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(finesDb) << endl;
        return;
    }

    sqlite3_bind_double(stmt, 1, fineAmount);
    sqlite3_bind_int(stmt, 2, studentId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Failed to update fine amount: " << sqlite3_errmsg(finesDb) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);

    if (updateBalance(db, studentId, -fineAmount)) {
        cout << "Fine paid successfully!" << endl;
        string textmsg = "Paid Fine of " + to_string(fineAmount) +".";
        insertActivity(studentId,textmsg);
    }
}
