#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QMainWindow>
#include "vendors/sqlite/sqlite3.h"
#include<QtSql/QSqlQueryModel>
#include<QDebug>
#include <QStandardItemModel>
namespace Ui {
class activity;
}

class activity : public QMainWindow
{
    Q_OBJECT

public:
    explicit activity(int id, QWidget *parent = nullptr);
    ~activity();


private:
    Ui::activity *ui;
    QStandardItemModel *model;
};

#endif // ACTIVITY_H
