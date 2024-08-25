#include "secondpage.h"
#include "ui_secondpage.h"


secondpage::secondpage(int id,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::secondpage)
{
    studentid = id;
     ui->setupUi(this);

     label_stud=new QLabel(this);
     label_stud->setGeometry(795,220,135,40);
     label_stud->setStyleSheet("QLabel{ background-color: grey;color: black;font: 600 14pt; Segoe UI;border:4px solid rgb(128,128,128);border-radius: 10px;}");
     label_stud->setText("Student Id:");
     label_stud->setAlignment(Qt::AlignCenter);

     label_id=new QLabel(this);
     label_id->setGeometry(910,220,70,40);
     label_id->setStyleSheet("QLabel{ background-color: grey;color: black;font: 600 14pt; Segoe UI;border:4px solid rgb(128,128,128);border-radius: 10px;}");
     label_id->setText(QString::fromStdString(std::to_string(id)));
     label_id->setAlignment(Qt::AlignCenter);



    label_1=new QLabel("KU Library",this);
    label_1->setStyleSheet("QLabel{  color: rgb(0, 0, 0);font: 800 14pt; Segoe UI;}");
    label_1->setGeometry(840,180,200,30);
    logo_1=new QLabel(this);
    logo_1->setGeometry(810,10,150,150);
    QPixmap ku_1(":images/4.jpg");
    logo_1->setPixmap(ku_1);
    logo_1->setScaledContents(true);
    choose=new QLabel("Choose the following options:",this);
    choose->setGeometry(780,280,250,40);
    choose->setStyleSheet("QLabel{ color: rgb(0, 0, 0);font: 600 12pt; Segoe UI;}");
    add=new QPushButton("Add",this);
    add->setGeometry(760,340,250,50);
    add->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");
    remove=new QPushButton("Remove",this);
    remove->setGeometry(760,420,250,50);
    remove->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");
    exit=new QPushButton("Exit",this);
    exit->setGeometry(760,500,250,50);
    exit->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");

    connect(exit,&QPushButton::clicked,this,&secondpage::onExit);
    connect(add,&QPushButton::clicked,this,&secondpage::onadd);
    connect(remove,&QPushButton::clicked,this,&secondpage::onRemove);

}

secondpage::~secondpage()
{
    delete ui;
}
void secondpage::onExit()
{
    this->hide();


}
void secondpage::onadd()
{

    p3=new addpage(studentid,this);
    p3->show();
}
void secondpage::onRemove()
{
    p4=new fourthpage(studentid,this);
    p4->show();
}
