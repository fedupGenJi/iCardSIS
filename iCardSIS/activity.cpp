#include "activity.h"
#include "ui_activity.h"
#include "QtSql/QSqlError"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlQueryModel"
#include "vendors/sqlite/sqlite3.h"
#include <string>
#include <iostream>
activity::activity(int id, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::activity)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model->setHorizontalHeaderLabels({"DATE","ACTIVITY"});

    ui->listView->setModel(model);
    ui->listView->horizontalHeader()->setStretchLastSection(true);
    ui->listView->setColumnWidth(0, 100);
    ui->listView->setColumnWidth(1, 300);

    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::string dbName = "A:/iCardSIS/pages/auditLogPage/auditLog.db"; // Replace with your database name
    std::string tableName = "Student_" + std::to_string(id);
    std::string query = "SELECT * FROM " + tableName;

    // Open the database
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Execute the query and display the table
    //std::cout << "Table " << tableName << ":\n";
    int colCount = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        QList<QStandardItem *> rowItems;
        for (int col = 0; col < colCount; col++) {
            QString data = reinterpret_cast<const char *>(sqlite3_column_text(stmt, col));
            rowItems.append(new QStandardItem(data));
            //std::cout << sqlite3_column_text(stmt, col) << " ";
        }
        model->appendRow(rowItems);
        //std::cout << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

activity::~activity()
{
    delete ui;
}
