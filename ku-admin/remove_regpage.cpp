#include "remove_regpage.h"
#include "ui_remove_regpage.h"
#include "registrationMain.hpp"

remove_regpage::remove_regpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::remove_regpage)
{
    ui->setupUi(this);
}

remove_regpage::~remove_regpage()
{
    delete ui;
}

//on remove clicked check if success or error and close the dialog if success

void remove_regpage::on_pushButton_delete_1_clicked()
{
    QString email = ui->lineEdit_remEmail->text();
    std :: string gmail = email.toStdString();
    if (removeUserByGmail(gmail)) {
        removeFromPhoneNIdTable(gmail);
    }

    emit goback_from_11();
}

