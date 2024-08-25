#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <string>
#include <iostream>
#include "DatabaseModel.h"
#include <QMessageBox>
using namespace std;

class DatabaseHelper {
public:

    DatabaseHelper(const string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
        } else {
            cout << "Opened database successfully" << endl;
        }
    }

    ~DatabaseHelper() {
        sqlite3_close(db);
    }

    void Errormessage(const QString &errorMessage) {
        QMessageBox::critical(nullptr, "Error", errorMessage);
    }
    void Successmessage(const QString &message){
        QMessageBox::information(nullptr,"Sucess!",message);
    }

    void createTable() {
        const char* sql_create_table =
            "CREATE TABLE IF NOT EXISTS studentID ("
            "id INTEGER PRIMARY KEY, "
            "firstName TEXT, "
            "middleName TEXT, "
            "lastName TEXT, "
            "dob TEXT, "
            "bloodGroup TEXT, "
            "email TEXT, "
            "course TEXT, "
            "yearOfEnrollment INTEGER, "
            "imgpath TEXT);";
        
        char* errMsg = 0;
        int rc = sqlite3_exec(db, sql_create_table, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            Errormessage("ERROR!");
            sqlite3_free(errMsg);
        } else {
            cout << "Table created successfully" << endl;
        }
    }

    bool idExists(int id) {
        const char* sql_select = "SELECT 1 FROM studentID WHERE id = ?;";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, sql_select, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
            return false;
        }

        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        bool exists = (rc == SQLITE_ROW);

        sqlite3_finalize(stmt);

        return exists;
    }

    void insertData(const DatabaseModel& model) {
        const char* sql_insert = "INSERT INTO studentID (id, firstName, middleName, lastName, dob, bloodGroup, email, course, yearOfEnrollment, imgpath) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
            return;
        }

        sqlite3_bind_int(stmt, 1, model.id);
        sqlite3_bind_text(stmt, 2, model.firstName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, model.middleName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, model.lastName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, model.dob.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, model.bloodGroup.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, model.email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, model.course.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 9, model.yearOfEnrollment);
        sqlite3_bind_text(stmt, 10, model.imgpath.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
        } else {
            cout << "Data inserted successfully" << endl;
            Successmessage("Data inserted successfully!");
        }

        sqlite3_finalize(stmt);
    }

    void deleteData(int id) {
        if (!idExists(id)) {
            cerr << "Error: ID " << id << " does not exist." << endl;
            Errormessage("Id does not exist.");
            return;
        }

        const char* sql_delete = "DELETE FROM studentID WHERE id = ?;";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, sql_delete, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
            return;
        }

        sqlite3_bind_int(stmt, 1, id);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << endl;
            Errormessage("ERROR!");
        } else {
            cout << "Data deleted successfully" << endl;
            Successmessage("Data deleted successfully!");
        }

        sqlite3_finalize(stmt);
    }

private:
    sqlite3* db = nullptr;
};

#endif // DATABASEHELPER_H
