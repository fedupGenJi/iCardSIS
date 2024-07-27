#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include "include/databaseoperation.h"
#include "include/balanceOperation.h"
#include "include/fineOperation.h"
#include "include/busSubscription.h"

using namespace std;

void showOptions(sqlite3 *db, sqlite3 *finesDb, int studentId);

int main() {
    sqlite3 *db, *finesDb;
    int rc = sqlite3_open("A:\\iCardSIS\\databases\\ku-database\\ku-database.db", &db);
    if (rc) {
        cerr << "Can't open ku-database: " << sqlite3_errmsg(db) << endl;
        return rc;
    }

    rc = sqlite3_open("A:\\iCardSIS\\databases\\library-database\\library.db", &finesDb);
    if (rc) {
        cerr << "Can't open fine database: " << sqlite3_errmsg(finesDb) << endl;
        sqlite3_close(db);
        return rc;
    }

    int studentId;
    cout << "Enter student ID: ";
    cin >> studentId;

    if (!checkStudentId(db, studentId)) {
        cerr << "Student ID not found!" << endl;
        sqlite3_close(db);
        sqlite3_close(finesDb);
        return 1;
    }

    showOptions(db, finesDb, studentId);

    sqlite3_close(db);
    sqlite3_close(finesDb);
    return 0;
}

void showOptions(sqlite3 *db, sqlite3 *finesDb, int studentId) {
    int option;
    while (true) {
        cout << "Choose an option: \n1. Add Balance\n2. Transfer Balance\n3. Pay Fines\n4. Bus Subscription\n5. Exit\n";
        cin >> option;

        switch (option) {
            case 1:
                addBalance(db, studentId);
                break;
            case 2:
                transferBalance(db, studentId);
                break;
            case 3:
                payFines(finesDb, db, studentId);
                break;
            case 4:
                bus_Subscription(db, studentId);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return;
            default:
                cerr << "Invalid option!" << endl;
                break;
        }
    }
}

//use this function to create table for Balance
/*int main() {
    sqlite3* DB;
    int exit = sqlite3_open("A:\\iCardSIS\\databases\\ku-database\\ku-database.db", &DB);

    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    } else {
        std::cout << "Opened Database Successfully!" << std::endl;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Balance ("
                      "studentId INTEGER PRIMARY KEY, "
                      "balance INTEGER DEFAULT 0);";

    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }
    sqlite3_close(DB);
    return 0;
}*/