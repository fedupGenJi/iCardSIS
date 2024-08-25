#include "kulibrary.h"
#include "ui_kulibrary.h"
#include "LibManager.hpp"
#include "secondpage.h"
#include "fine.cpp"

KULibrary::KULibrary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KULibrary)
{
    ui->setupUi(this);


    label=new QLabel("KU Library",this);
    label->setStyleSheet("QLabel{  color: rgb(0, 0, 0);font: 700 14pt; Segoe UI;}");
    label->setGeometry(820,180,200,30);
    student_id=new QLineEdit(this);
    student_id->setPlaceholderText("Enter student id");
    student_id->setGeometry(760,250,250,40);
    student_id->setStyleSheet("QLineEdit{background-color: rgb(255,255, 255);  color: rgb(0,0,0);font: 500 10pt; Times New Roman;}");
    logo=new QLabel(this);
    logo->setGeometry(800,10,150,150);
    QPixmap ku(":images/4.jpg");
    logo->setPixmap(ku);
    logo->setScaledContents(true);
    button=new QPushButton("Check Student ID",this);
    button->setGeometry(760,340,250,50);
    button->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");

    function_button=new QPushButton("Fine Calculator",this);
    function_button->setGeometry(760,400,250,50);
    function_button->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:5px solid rgb(0,0,0);border-radius: 20px;font: 700 16pt Segoe UI;background-color: rgb(0, 0, 0);}QPushButton:pressed{background-color: rgb(170, 0, 0);}");


    connect(button,&QPushButton::clicked,this,&KULibrary::openSecondPage);
    connect(function_button,&QPushButton::clicked,this,&KULibrary::call_function);


}

KULibrary::~KULibrary()
{
    delete ui;
}

//if student id matches:call this function

void KULibrary::openSecondPage()
{
    QString id=student_id->text();
    std:: string studentID = id.toStdString();

    LibManager libManager("A:/iCardSIS/databases/library-database/library.db");


    // Check if student ID exists in the Borrowers table
    if (!libManager.checkBorrower(std::stoi(studentID))) {
        std::cerr << "Error: No such user ID found." << std::endl;
        QMessageBox Error ;
        Error.setText("Student ID not FOUND!");
        Error.setStyleSheet("QMessageBox{background color:white;color-black;");
        Error.setIcon(QMessageBox::Warning);
        Error.exec();

        return;
    }
    page_2= new secondpage(std::stoi(studentID),this);
    page_2->show();

}

void KULibrary::call_function()
{

    if (finecalculator() == 1) {
        std::cerr << "Error: No such user ID found." << std::endl;
        QMessageBox Error ;
        Error.setText("Error during Fine calculation");
        Error.setStyleSheet("QMessageBox{background color:white;color-black;");
        Error.setIcon(QMessageBox::Warning);
        Error.exec();

        return;
    }
    dialog=new functiondialog(this);
    dialog->show();




    /*else
    msg.setText("Error");

    msg.setStyleSheet("QMessageBox{background-color:white;color:black;}");


    msg.setIcon(QMessageBox::Warning);
    msg.exec();
*/

}



//else display error message using QMessageBox
