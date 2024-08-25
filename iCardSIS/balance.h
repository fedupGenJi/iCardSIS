#ifndef BALANCE_H
#define BALANCE_H
#include<addbalance.h>
#include<transferbalance.h>
#include <QMainWindow>
#include <subscription.h>
#include "vendors/sqlite/sqlite3.h"
#include <payfine.h>

namespace Ui {
class balance;
}

class balance : public QMainWindow
{
    Q_OBJECT

public:
    explicit balance(int id,QWidget *parent = nullptr);
    int studentId;
    sqlite3 *db, *finesDb;
    ~balance();

private slots:

    void returnback_from_addbalance();
    void returnback_from_transferbalance();
    void returnback_from_subscription();
    void returnback_from_fine();
    void on_pushButton_addbalance_clicked();
    void updatePage();
    void on_pushButton_transferbalance_clicked();





    void on_pushButton__bus_clicked();

    void on_payFine_clicked();

private:
    Ui::balance *ui;
    addbalance *addbal;
    transferbalance *transferbal;
    subscription *sub;
    payFine *fine;
};

#endif // BALANCE_H
