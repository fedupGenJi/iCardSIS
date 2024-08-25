#include "books.h"
#include "ui_books.h"
#include "QMessageBox"
#include "QtSql/QSqlError"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlQueryModel"
#include "vendors/sqlite/sqlite3.h"
#include <string>
#include <iostream>

books::books(int id,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::books)
    , model(new QStandardItemModel(this))
{
    studentId = id;
    ui->setupUi(this);
    model->setHorizontalHeaderLabels({"Book ID", "Book Name", "Borrowed Date", "Deadline", "Days Dued"});

    ui->tableView->setModel(model);

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
        //int id = sqlite3_column_int(stmt, 0);
        //int studentID = sqlite3_column_int(stmt,1);
        const unsigned char* bookId = sqlite3_column_text(stmt,2);
        const unsigned char* bookName = sqlite3_column_text(stmt, 3);
        const unsigned char* borrowedDate = sqlite3_column_text(stmt, 4);
        const unsigned char* deadline = sqlite3_column_text(stmt, 5);
        int daysDued = sqlite3_column_int(stmt, 6);

        //std::string s(reinterpret_cast<const char*>(bookId));
        //QString s1 = QString::fromStdString(s);
        QString s1 = QString::fromUtf8(reinterpret_cast<const char*>(bookId));
        // std::string ss(reinterpret_cast<const char*>(bookName));
        // QString s2 = QString::fromStdString(ss);
        QString s2 = QString::fromUtf8(reinterpret_cast<const char*>(bookName));
        // std::string ss1(reinterpret_cast<const char*>(borrowedDate));
        // QString s3 = QString::fromStdString(ss1);
        QString s3 = QString::fromUtf8(reinterpret_cast<const char*>(borrowedDate));
        // std::string ss2(reinterpret_cast<const char*>(deadline));
        // QString s4 = QString::fromStdString(ss2);
        QString s4 = QString::fromUtf8(reinterpret_cast<const char*>(deadline));
        QString s5 = QString::fromStdString(std::to_string(daysDued));

        QList<QStandardItem*> items;
        items.append(new QStandardItem(s1));
        items.append(new QStandardItem(s2));
        items.append(new QStandardItem(s3));
        items.append(new QStandardItem(s4));
        items.append(new QStandardItem(s5));

        model->appendRow(items);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

books::~books()
{
    delete ui;
}



