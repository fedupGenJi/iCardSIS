#include "fourthpage.h"
#include "ui_fourthpage.h"
#include "LibManager.hpp"

fourthpage::fourthpage(int id,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fourthpage)
{
    student_id = id;
    /*label_id=new QLabel(this);
    label_id->setGeometry(910,220,70,40);
    label_id->setStyleSheet("QLabel{ background-color: grey;color: black;font: 600 14pt; Segoe UI;border:4px solid rgb(128,128,128);border-radius: 10px;}");
    label_id->setText(QString::fromStdString(std::to_string(id)));
    label_id->setAlignment(Qt::AlignCenter);*/

    ui->setupUi(this);
    label_3=new QLabel("KU Library",this);
    label_3->setStyleSheet("QLabel{  color: rgb(0, 0, 0);font: 800 14pt; Segoe UI;}");
    label_3->setGeometry(532,210,200,30);
    logo_3=new QLabel(this);
    logo_3->setGeometry(515,50,150,150);
    QPixmap ku_3(":images/4.jpg");
    logo_3->setPixmap(ku_3);
    logo_3->setScaledContents(true);
    book_id_1=new QLineEdit(this);
    book_id_1->setPlaceholderText("Enter book id");
    book_id_1->setGeometry(480,320,250,40);
    book_id_1->setStyleSheet("QLineEdit{background-color: rgb(255,255, 255);  color: rgb(0,0,0);font: 500 10pt; Times New Roman;}");
    confirm=new QPushButton("Confirm",this);
    confirm->setGeometry(480,500,250,50);
    confirm->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");


    connect(confirm,&QPushButton::clicked,this,&fourthpage::on_confirm);
}

void fourthpage :: on_confirm()
{
    LibManager libManager("A:/iCardSIS/databases/library-database/library.db");


    QString idx=book_id_1->text();
    std :: string bookID = idx.toStdString();

    libManager.removeBook(student_id, bookID);

    this->hide();
}
fourthpage::~fourthpage()
{
    delete ui;

}
//on confirm clicked remove the book from the database.
