#include "reg_admin.h"
#include "ui_reg_admin.h"

reg_admin::reg_admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::reg_admin)
{
    ui->setupUi(this);
}

reg_admin::~reg_admin()
{
    delete ui;
}

void reg_admin::on_pushButton_regremove_clicked()
{
    remp=new remove_regpage(this);
    connect(remp,&remove_regpage::goback_from_11,this,&reg_admin::returnback_from_1);
    remp->show();
    //this->hide();
}


void reg_admin::on_pushButton_back_3_clicked()
{
    emit goback_from_admin();
}

void reg_admin :: returnback_from_1()
{
    remp->hide();
    emit goback_from_admin();
}

void reg_admin::on_pushButton_change_clicked()
{
    num = new change_num(this);
    connect(num,&change_num::goback_from_22,this,&reg_admin::returnback_from_2);
    num->show();
}

void reg_admin :: returnback_from_2()
{
    num->hide();
    emit goback_from_admin();
}
