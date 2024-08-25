#ifndef BOOKS_H
#define BOOKS_H

#include <QMainWindow>
#include "vendors/sqlite/sqlite3.h"
#include<QtSql/QSqlQueryModel>
#include<QDebug>
#include <QStandardItemModel>

namespace Ui {
class books;
}

class books : public QMainWindow
{
    Q_OBJECT

public:
    explicit books(int id, QWidget *parent = nullptr);
    int studentId;
    ~books();



private slots:

private:
    Ui::books *ui;
     QStandardItemModel *model;
};

#endif // BOOKS_H
