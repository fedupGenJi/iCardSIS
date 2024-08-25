#include "transferbalance.h"
#include "ui_transferbalance.h"
#include "include/balanceOperation.h"

transferbalance::transferbalance(int id, sqlite3* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transferbalance)
{
    ui->setupUi(this);
    idxx = id;
    dbx = db;
}

transferbalance::~transferbalance()
{
    delete ui;
}

void transferbalance::on_pushButton_addbalance_clicked()
{
    QString phone = ui->lineEdit->text();
    QString moneyx = ui->lineEdit_2->text();
    receipentNumber = phone.toStdString();
    money = moneyx.toStdString();
    amount = std::stoi(money);

    if(transferBalance(dbx,idxx,receipentNumber,amount))
    {
        emit goback_from_transferbalance();
    }
    else
        {
            emit goback_from_transferbalance();
        }
}


void transferbalance::on_pushButton_clicked()
{
    emit goback_from_transferbalance();
}

