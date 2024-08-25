#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainpage)
{
    ui->setupUi(this);
}

Mainpage::~Mainpage()
{
    delete ui;
}

void Mainpage::on_pushButton_add_clicked()
{
    addku=new addtoku(this);
    connect(addku,&addtoku::goback_from_add,this,&Mainpage::returnback_from_add);
    addku->show();
    this->hide();
}


void Mainpage::on_pushButton_up_clicked()
{
    upd=new updatedb(this);
    connect(upd,&updatedb::goback_from_update,this,&Mainpage::returnback_from_update);
    upd->show();
    this->hide();
}


void Mainpage::on_pushButton_reg_clicked()
{
    adm=new reg_admin(this);
    connect(adm,&reg_admin::goback_from_admin,this,&Mainpage::returnback_from_admin);
    adm->show();
    this->hide();
}


void Mainpage::on_pushButton_canteen_clicked()
{
    can=new canteen(this);
    connect(can,&canteen::goback_from_canteen,this,&Mainpage::returnback_from_canteen);
    can->show();
    this->hide();
}

void Mainpage::returnback_from_add()
{
    this->show();
    addku->hide();

}

void Mainpage::returnback_from_update()
{
    this->show();
    upd->hide();

}

void Mainpage::returnback_from_admin()
{
    this->show();
    adm->hide();

}
void Mainpage::returnback_from_canteen()
{
    this->show();
    can->hide();

}
