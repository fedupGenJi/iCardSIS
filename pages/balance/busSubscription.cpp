#include "include/busSubscription.h"
#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include<ctime>
#include "A:\iCardSIS\pages\auditLogPage\auditInput.h"
#include "A:\iCardSIS\pages\balance\include\busSubscription.h"
using namespace std;

string getDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return string(buffer);
}

// Function to get the deadline date (current date + 30 days)
string getDeadlineDate() {
    time_t t = time(nullptr) + (30 * 24 * 60 * 60);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return string(buffer);
}

// Function to update the Transportation table and reduce the balance
void updateTransportation(sqlite3* db, int studentId, int choice) {
     if (!db) {
        std::cerr << "Invalid database connection." << endl;
        return;
    }
    const char* routePlace;
    int cost;
    switch (choice) {
        case 1:
            routePlace = "Sanga";
            cost = 200;
            break;
        case 2:
            routePlace = "Bhaktapur";
            cost = 400;
            break;
        case 3:
            routePlace = "Kathmandu";
            cost = 500;
            break;
        default:
            cerr << "Invalid choice." << endl;
            return;
    }

    sqlite3_stmt* stmt;
    const char* checkBalanceSQL = "SELECT balance FROM Balance WHERE studentId = ?;";
    int rc = sqlite3_prepare_v2(db, checkBalanceSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        cerr << "Student ID " << studentId << " does not have a balance entry." << endl;
        sqlite3_finalize(stmt);
        return;
    }

    int balance = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    if (balance < cost) {
        cerr << "Insufficient balance." << endl;
        return;
    }

    // Update the Transportation table
    const char* updateTransSQL = "INSERT OR REPLACE INTO Transportation (StudentId, Status, RoutePlace, Deadline, DaysLeft) VALUES (?, 'ACTIVE', ?, ?, 30);";
    rc = sqlite3_prepare_v2(db, updateTransSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);
    sqlite3_bind_text(stmt, 2, routePlace, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, getDeadlineDate().c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Failed to update Transportation table: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return;
    }
    cout << "Bus Subscription is added!" << endl;
    string textmsg = "Bus subscription is added.";
        insertActivity(studentId,textmsg);
    sqlite3_finalize(stmt);

    // Reduce the balance in the Balance table
    const char* updateBalanceSQL = "UPDATE Balance SET balance = balance - ? WHERE studentId = ?;";
    rc = sqlite3_prepare_v2(db, updateBalanceSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, cost);
    sqlite3_bind_int(stmt, 2, studentId);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Failed to update Balance table: " << sqlite3_errmsg(db) << endl;
    }
    cout << "Balance is deducted!" << endl;
    string balancemsg = cost + " is deducted for Bus Subscription.";
        insertActivity(studentId,balancemsg);
    sqlite3_finalize(stmt);
}

void displayRoute(sqlite3* db, int studentId) {
    cout << "Choose a route:\n";
    cout << "1. Sanga Rs:200/month\n";
    cout << "2. Bhaktapur Rs:400/month\n";
    cout << "3. Kathmandu Rs:500/month\n";

    int choice;
    cin >> choice;
    updateTransportation(db, studentId, choice);
}


void checkForTable(sqlite3* db, int studentId) {
    char* errMsg = 0;
    int rc;

    if (!db) {
        std::cerr << "Invalid database connection." << endl;
        return;
    }

    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Transportation(
            studentId INT PRIMARY KEY NOT NULL,
            status TEXT DEFAULT 'INACTIVE' ,
            routePlace TEXT ,
            deadline TEXT ,
            daysLeft INT DEFAULT 0
        );
    )";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    } else {
        cout << "Table created successfully or already exists\n";
    }

    // Check if studentId exists
    sqlite3_stmt* stmt;
    const char* checkStudentSQL = "SELECT COUNT(*) FROM Transportation WHERE StudentId = ?;";

    rc = sqlite3_prepare_v2(db, checkStudentSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 0) {
            cerr << "Error: Student ID " << studentId << " does not exist in the Transportation table." << endl;
        } else {
            cout << "Student ID " << studentId << " exists in the Transportation table." << endl;
            displayRoute(db, studentId);
        }
    }

    sqlite3_finalize(stmt);
}

void bus_Subscription(sqlite3 *db, int studentId) {
    checkForTable(db,studentId);
}