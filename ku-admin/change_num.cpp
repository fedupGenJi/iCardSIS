#include "change_num.h"
#include "ui_change_num.h"
#include "registrationMain.hpp"
change_num::change_num(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::change_num)
{
    ui->setupUi(this);
}

change_num::~change_num()
{
    delete ui;
}

void change_num::on_pushButton_change_clicked()
{
    QString mail = ui->lineEdit_askEmail->text();
    QString number = ui->lineEdit_asknum->text();
    std::string gmail = mail.toStdString();
    std::string phoneNumber = number.toStdString();
    if (changePhoneNumber(gmail, phoneNumber)) {
        removeFromPhoneNIdTable(gmail);
    }

    emit goback_from_22();
}

