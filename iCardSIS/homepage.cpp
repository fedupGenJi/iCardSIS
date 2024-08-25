#include "homepage.h"
#include "ui_homepage.h"
#include "studentInfo.h"
#include "QPixmap"
#include <string>
homepage::homepage(int id, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::homepage)
{
    homepage::studentId = id;
    ui->setupUi(this);
    ui->id->setText(QString::fromStdString(std::to_string(id)));
    StudentInfo studentInfo = getStudentInfo(id);

    ui->studentName->setText(QString::fromStdString(studentInfo.fullName));
    ui->studentDOB->setText(QString::fromStdString(studentInfo.dateOfBirth));
    ui->studentCourse->setText(QString::fromStdString(studentInfo.course));
    ui->bloodGroup->setText(QString::fromStdString(studentInfo.bloodGroup));
    ui->year->setText(QString::fromStdString(std::to_string(studentInfo.enrollmentYear)));
    //not using any relativePath
    std::string finalphotoPath = "A:/FINAL-iCardSIS/iCardSIS/"+studentInfo.photoPath;
    imagePath = QString::fromStdString(finalphotoPath);
    QPixmap path(imagePath);
    ui->studentPhoto->setPixmap(path);
    ui->studentPhoto->setScaledContents(true);
}

homepage::~homepage()
{
    delete ui;
}




void homepage::on_pushButton_exit_clicked()
{
    this->hide();
}


void homepage::on_pushButton_balance_clicked()
{
    bal= new balance(studentId,this);
    bal->show();
}


void homepage::on_pushButton_library_clicked()
{
    bks =new books(studentId,this);
    bks->show();
}


void homepage::on_pushButton_transport_clicked()
{
    transport=new transportation(studentId,imagePath,this);
    transport->show();
}


void homepage::on_pushButton_activity_clicked()
{
    act=new activity(studentId,this);
    act->show();
}

