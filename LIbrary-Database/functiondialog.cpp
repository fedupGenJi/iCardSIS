#include "functiondialog.h"
#include "ui_functiondialog.h"

functiondialog::functiondialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::functiondialog)
{
    ui->setupUi(this);

}

functiondialog::~functiondialog()
{

    delete ui;
}

void functiondialog::on_pushButton_clicked()
{
    this->hide();
}

