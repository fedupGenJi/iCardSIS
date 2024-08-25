#include "addtoku.h"
#include "ui_addtoku.h"

addtoku::addtoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::addtoku)
{
    ui->setupUi(this);
}

addtoku::~addtoku()
{
    delete ui;
}

void addtoku::on_pushButton_add_1_clicked()
{
    insert=new data_addpage(this);
    connect(insert,&data_addpage::goback_from_insert,this,&addtoku::returnback_from_insert);
    insert->show();
}


void addtoku::on_pushButton_remove_clicked()
{
    rem= new data_removepage(this);
    connect(rem,&data_removepage::goback_from_rem,this,&addtoku::returnback_from_rem);
    rem->show();
}


void addtoku::on_pushButton_back_clicked()
{
    emit goback_from_add();
}

void addtoku::returnback_from_rem()
{
    rem->hide();
    emit goback_from_add();
}

void addtoku::returnback_from_insert()
{
    insert->hide();
    emit goback_from_add();
}
