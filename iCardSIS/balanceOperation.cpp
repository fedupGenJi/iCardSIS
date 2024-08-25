#include "include/balanceOperation.h"
#include "include/databaseOperation.h"
#include "auditInput.h"
#include <iostream>
#include <string>
#include <QMessageBox>
using namespace std;

void Error(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
void Success(const QString &message){
    QMessageBox::information(nullptr,"Sucess!",message);
}

bool addBalances(sqlite3 *db, int studentId, string phoneNumber, int amount) {

    // Check if phone number is linked to the student ID
    sqlite3_stmt *stmt;
    const char *sql = "SELECT studentId FROM phoneNId WHERE phoneNumber = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        Error("ERROR!");
        return false;
    }

    sqlite3_bind_text(stmt, 1, phoneNumber.c_str(), -1, SQLITE_STATIC);

    bool valid = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int linkedStudentId = sqlite3_column_int(stmt, 0);
        valid = (linkedStudentId == studentId);
    }

    sqlite3_finalize(stmt);

    if (!valid) {
        cerr << "Phone number does not match the provided student ID!" << endl;
        Error("Phone number does not match the provided student ID!");
        return false;
    }

    if (updateBalance(db, studentId, amount)) {
        cout << "Balance added successfully!" << endl;
        string textmsg = "Balance of " + to_string(amount) + " added succesfully.";
        insertActivity(studentId,textmsg);
        Success("Balance Added Successfully");
    }
    return true;
}

bool transferBalance(sqlite3 *db, int studentId, string recipientPhoneNumber, int amount) {


    // Check if recipient phone number exists and get recipient student ID
    sqlite3_stmt *stmt;
    const char *sql = "SELECT studentId FROM phoneNId WHERE phoneNumber = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        Error("ERROR!");
        return false;
    }

    sqlite3_bind_text(stmt, 1, recipientPhoneNumber.c_str(), -1, SQLITE_STATIC);

    int recipientStudentId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        recipientStudentId = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (recipientStudentId == -1) {
        cerr << "Recipient phone number not found!" << endl;
        Error("Recipient phone number not found.");
        return false;
    }

    double senderBalance = getBalance(db, studentId);
    if (senderBalance < amount) {
        cerr << "Insufficient balance!" << endl;
        Error("Insufficient balance!");
        return false;
    }

    if (updateBalance(db, studentId, -amount) && updateBalance(db, recipientStudentId, amount)) {
        cout << "Balance transferred successfully to student ID: " << recipientStudentId << endl;
        string textmsg = "Balance of " + to_string(amount) + " transferred succesfully to " + to_string(recipientStudentId) + ".";
        insertActivity(studentId,textmsg);
        string text = "Balance of " + to_string(amount) + " received succesfully from " + to_string(studentId) + ".";
        insertActivity(recipientStudentId,text);
        Success("Balance transffered successfully!");
    }
    return true;
}
