#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <QDialog>
#include "vendors/sqlite/sqlite3.h"

namespace Ui {
class subscription;
}

class subscription : public QDialog
{
    Q_OBJECT

public:
    explicit subscription(int id, sqlite3* db,QWidget *parent = nullptr);
    int choice = 0;
    int idxx;
    sqlite3* dbx;
    ~subscription();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_subscribe_clicked();
    void on_pushButton_clicked();

signals:
    void goback_from_subscription();
private:
    Ui::subscription *ui;
};

#endif // SUBSCRIPTION_H
