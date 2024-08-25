#include "canteen.h"
#include "ui_canteen.h"
#include "canteenMain.h"

canteen::canteen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::canteen)
{
    ui->setupUi(this);
}

canteen::~canteen()
{
    delete ui;
}

//on continue check for error or success and display messagebox.

void canteen::on_pushButton_back_4_clicked()
{
    emit goback_from_canteen();
}


void canteen::on_pushButton_conti_clicked()
{
    QString student = ui->lineEdit_stud->text();
    QString bill = ui->lineEdit_bill->text();
    std::string studentId = student.toStdString();
    std::string billAmount = bill.toStdString();
    if (processTransaction(std::stoi(studentId),std::stoi(billAmount)))
    {
        emit goback_from_canteen();
    }
    else
    {
        emit goback_from_canteen();
    }
}

