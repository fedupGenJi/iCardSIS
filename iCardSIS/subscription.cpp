#include "subscription.h"
#include "ui_subscription.h"
#include "include/busSubscription.h"
subscription::subscription(int id, sqlite3* db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::subscription)
{
    idxx = id;
    dbx = db;
    ui->setupUi(this);
}

subscription::~subscription()
{
    delete ui;
}

void subscription::on_radioButton_clicked()
{
    choice = 3;
}


void subscription::on_radioButton_2_clicked()
{
    choice = 2;
}


void subscription::on_radioButton_3_clicked()
{
    choice = 1;
}


void subscription::on_pushButton_subscribe_clicked()
{
    if(checkForTable(dbx,idxx,choice))
    {
        emit goback_from_subscription();
    }
    else
    {
        emit goback_from_subscription();
    }
}


void subscription::on_pushButton_clicked()
{
    emit goback_from_subscription();
}

