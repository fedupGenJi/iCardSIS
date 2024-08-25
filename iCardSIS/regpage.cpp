#include "regpage.h"
#include "ui_regpage.h"
#include <QDialog>
#include "registration.h"
#include "QString"

regpage::regpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::regpage)
{
    ui->setupUi(this);
}

regpage::~regpage()
{
    delete ui;
}

void regpage::on_pushButton_clicked()
{
    QString name = ui->UserName->text();
    std::string userName = name.toStdString();
    QString email = ui->Email->text();
    std::string gmail = email.toStdString();
    QString pass = ui->pass->text();
    QString conpass = ui->conPass->text();
    std::string password = pass.toStdString();
    std::string confirm_password = conpass.toStdString();
    QString phone = ui->phoneNumber->text();
    std::string phoneNumber = phone.toStdString();

    if(registerUser(phoneNumber, password, confirm_password, gmail))
    {
        std::string message = "Welcome " + userName;
        completeMessage(QString::fromStdString(message));
        this->hide();
    }
}

