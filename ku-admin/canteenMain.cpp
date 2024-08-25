#include <iostream>
#include "sqlite/sqlite3.h"
#include "auditInput.h"
#include "canteenMain.h"
#include <QString>
#include <QMessageBox>
#include <string>

void Error(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
void Success(const QString &message){
    QMessageBox::information(nullptr,"Sucess!",message);
}

bool processTransaction(int studentId, int billAmount)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("A:\\iCardSIS\\databases\\ku-database\\ku-database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        Error("ERROR!");
        return false;
    }

    std::string sql = "SELECT balance FROM Balance WHERE studentId = ?;";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        Error("ERROR!");
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, studentId);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int currentBalance = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        if (currentBalance >= billAmount) {
            sql = "UPDATE Balance SET balance = balance - ? WHERE studentId = ?;";
            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                Error("ERROR!");
                sqlite3_close(db);
                return false;
            }

            sqlite3_bind_double(stmt, 1, billAmount);
            sqlite3_bind_int(stmt, 2, studentId);
            rc = sqlite3_step(stmt);
            if (rc == SQLITE_DONE) {
                std::cout << "Transaction successful. Balance deducted." << std::endl;
                std::string textmsg = "Bill amount of " + std::to_string(billAmount) + " deducted for canteen.";
                insertActivity(studentId,textmsg);
                Success("Transaction Successful");
                return true;
            } else {
                std::cerr << "Failed to update balance: " << sqlite3_errmsg(db) << std::endl;
                Error("ERROR!");
                return false;
            }
            sqlite3_finalize(stmt);
        } else {
            std::cout << "Insufficient balance." << std::endl;
            Error("Insufficient balance!!!");
            return false;
        }
    } else {
        std::cout << "Student ID not found." << std::endl;
        Error("Student Id not found!");
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_close(db);
    return true;
}
