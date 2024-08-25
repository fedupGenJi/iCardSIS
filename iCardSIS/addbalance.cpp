#include "addbalance.h"
#include "ui_addbalance.h"
#include "include/balanceOperation.h"
#include "vendors/sqlite/sqlite3.h"
#include <string>
addbalance::addbalance(int id, sqlite3* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addbalance)
{
    idxx = id;
    dbx = db;
    ui->setupUi(this);

}

addbalance::~addbalance()
{
    delete ui;
}

void addbalance::on_pushButton_addbalance_clicked()
{
    QString phone = ui->phoneNumber->text();
    QString money = ui->amount->text();
    phoneNumber = phone.toStdString();
    money2 = money.toStdString();
    amount = std::stoi(money2);

    if(addBalances(dbx,idxx,phoneNumber,amount))
    {
        emit goback_from_addbalance();
    }
    else
    {
        emit goback_from_addbalance();
    }
}


void addbalance::on_pushButton_clicked()
{
    emit goback_from_addbalance();
}

