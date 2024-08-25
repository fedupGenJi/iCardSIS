#include "transportation.h"
#include "ui_transportation.h"
#include "vendors/sqlite/sqlite3.h"
#include <iostream>
#include <string>
#include <QMessageBox>
void msgg(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
transportation::transportation(int id, QString x,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::transportation)
{
    ui->setupUi(this);
    QPixmap path(x);
    ui->studentPhoto_2->setPixmap(path);
    ui->studentPhoto_2->setScaledContents(true);
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* dbName = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    const char* query = "SELECT status, routePlace, deadline FROM Transportation WHERE studentId = ?";

    // Open the database
    if (sqlite3_open(dbName, &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the studentId parameter
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        std::cerr << "Error binding studentId: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the query and process the results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (status == "INACTIVE") {
            //std::cout << "Status: Inactive" << std::endl;
            ui->label_3->setText("INACTIVE");
            ui->label_4->hide();
            ui->label_5->hide();
            ui->label_6->hide();
            ui->label_8->hide();
        } else if (status == "ACTIVE") {
            std::string route = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string deadline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            QString s = QString::fromStdString(route);
            QString ss = QString::fromStdString(deadline);
            ui->label_3->setText("ACTIVE");
            ui->label_6->setText(s);
            ui->label_8->setText(ss);
            // std::cout << "Status: Active" << std::endl;
            // std::cout << "Route: " << route << std::endl;
            // std::cout << "Deadline: " << deadline << std::endl;
        } else {
            //std::cout << "Status is unknown or invalid." << std::endl;
        }
    } else {
        msgg("Error!");
        return;
        //std::cout << "Student ID not found in the Transportation table." << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

transportation::~transportation()
{
    delete ui;
}
