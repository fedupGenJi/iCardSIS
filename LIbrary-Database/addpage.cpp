#include "addpage.h"
#include "ui_addpage.h"
#include <regex>

#include <ctime>
#include <iostream>
#include "LibManager.hpp"

bool isValidDate(const std::string& date) {
    std::regex datePattern(R"((\d{4})-(\d{2})-(\d{2}))");
    std::smatch match;
    if (std::regex_match(date, match, datePattern)) {
        int year = std::stoi(match[1].str());
        int month = std::stoi(match[2].str());
        int day = std::stoi(match[3].str());

        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        std::tm time_in = { 0, 0, 0, day, month - 1, year - 1900 };
        std::time_t time_temp = std::mktime(&time_in);

        const std::tm *time_out = std::localtime(&time_temp);

        return (time_out->tm_year == time_in.tm_year
                && time_out->tm_mon == time_in.tm_mon
                && time_out->tm_mday == time_in.tm_mday);
    }
    return false;
}
addpage::addpage(int id,QWidget *parent)
    : QDialog(parent), ui(new Ui::addpage)
{
    student_id = id;
    /*label_id=new QLabel(this);
    label_id->setGeometry(910,220,70,40);
    label_id->setStyleSheet("QLabel{ background-color: grey;color: black;font: 600 14pt; Segoe UI;border:4px solid rgb(128,128,128);border-radius: 10px;}");
    label_id->setText(QString::fromStdString(std::to_string(id)));
    label_id->setAlignment(Qt::AlignCenter);*/


    ui->setupUi(this);
    label_2=new QLabel("KU Library",this);
    label_2->setStyleSheet("QLabel{  color: rgb(0, 0, 0);font: 800 14pt; Segoe UI;}");
    label_2->setGeometry(532,210,200,30);
    logo_2=new QLabel(this);
    logo_2->setGeometry(515,50,150,150);
    QPixmap ku_2(":images/4.jpg");
    logo_2->setPixmap(ku_2);
    logo_2->setScaledContents(true);
    fill=new QLabel("Please fill the following details:",this);
    fill->setGeometry(480,250,250,40);
    fill->setStyleSheet("QLabel{ color: rgb(0, 0, 0);font: 600 12pt; Segoe UI;}");
    book_id=new QLineEdit(this);
    book_id->setPlaceholderText("Enter book id");
    book_id->setGeometry(480,320,250,40);
    book_id->setStyleSheet("QLineEdit{background-color: rgb(255,255, 255);  color: rgb(0,0,0);font: 500 10pt; Times New Roman;}");
    book_name=new QLineEdit(this);
    book_name->setPlaceholderText("Enter book name");
    book_name->setGeometry(480,380,250,40);
    book_name->setStyleSheet("QLineEdit{background-color: rgb(255,255, 255);  color: rgb(0,0,0);font: 500 10pt; Times New Roman;}");
    submission_date=new QLineEdit(this);
    submission_date->setPlaceholderText("yyyy-mm-dd");
    submission_date->setGeometry(480,440,250,40);
    submission_date->setStyleSheet("QLineEdit{background-color: rgb(255,255, 255);  color: rgb(0,0,0);font: 500 10pt; Times New Roman;}");
    done=new QPushButton("Done",this);
    done->setGeometry(480,500,250,50);
    done->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");

    connect(done,&QPushButton::clicked,this,&addpage::on_done);
}

addpage::~addpage()
{
    delete ui;
}

void addpage::on_done()
{
    LibManager libManager("A:/iCardSIS/databases/library-database/library.db");
    QString idx=book_id->text();
    QString name=book_name->text();
    QString date=submission_date->text();
    std :: string bookID = idx.toStdString();
    std :: string bookName = name.toStdString();
    std :: string submissionDate = date.toStdString();
    if (!isValidDate(submissionDate)) {
        std::cerr << "Invalid Date format" << std::endl;
        QMessageBox Error ;
        Error.setText("USE VALID DATE FORMAT!");
        Error.setStyleSheet("QMessageBox{background color:white;color-black;");
        Error.setIcon(QMessageBox::Warning);
        Error.exec();

        return;
    }
    libManager.addBook( student_id , bookID, bookName, submissionDate);
    this->hide();
}
