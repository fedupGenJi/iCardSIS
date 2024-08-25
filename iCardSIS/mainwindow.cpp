 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include<regpage.h>
#include <QDialog>
#include<QMessageBox>
#include"vendors/sqlite/sqlite3.h"
#include<iostream>

void showError(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}

bool verifyLogin(std::string& mobile_number, std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    bool login_successful = false;

    if (sqlite3_open("A:\\iCardSIS\\databases\\login-database\\registration.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT password FROM Users WHERE mobile_number = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, mobile_number.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string stored_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                if (password == stored_password) {
                    login_successful = true;
                } else {
                    std::cout << "Incorrect password.\n";
                    showError("Incorrect Password!");
                }
            } else {
                std::cout << "Phone number not registered.\n";
                showError("Phone number not registered!");
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
            showError("ERROR!");
        }
        sqlite3_close(db);
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        showError("ERROR!");
    }
    return login_successful;
}

//function to generate a encryption
std::string generatecrypt(std::string data)
{
    unsigned int result(0);

    for(unsigned int ch : data)
        result=ch + (result<<4) + (result<<10) - result;

    return std::to_string(result);
}

int getStudentIdFromPhoneNumber(const std::string& phoneNumber) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    int studentId = -1; // Default value indicating not found

    // Open the SQLite database
    rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return studentId;
    }

    // Prepare the SQL statement
    std::string sql = "SELECT studentId FROM phoneNId WHERE phoneNumber = ?";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return studentId;
    }

    // Bind the phone number to the statement
    rc = sqlite3_bind_text(stmt, 1, phoneNumber.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind phone number: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return studentId;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        studentId = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Database not updated. Phone number not found." << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return studentId;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label=new QLabel("Login",this);
    label->setStyleSheet("QLabel{  background-color:grey ;color: rgb(255, 255, 255);font:800 16pt Times New Roman;}");
    label->setGeometry(-80,230,1700,50);
    label->setAlignment(Qt::AlignCenter);

    enter=new QLabel("Please enter your credentials here:",this);
    enter->setStyleSheet("QLabel{ color: black;font:700 12pt Times New Roman;}");
    enter->setGeometry(640,300,300,50);

    phone=new QLineEdit(this);
    phone->setPlaceholderText("Enter your phone number");
    phone->setGeometry(640,350,250,40);
    phone->setStyleSheet("QLineEdit{  background-color: grey;color: rgb(255, 255, 255);font: 12pt Times New Roman;border:3px grey;border-radius:10px;padding-left: 2px;}"
                         "QLineEdit:focus {background-color: black;}");

    password=new QLineEdit(this);
    password->setPlaceholderText("Enter password");
    password->setGeometry(640,410,250,40);
    password->setStyleSheet("QLineEdit{  background-color: grey;color: rgb(255,255,255);font: 12pt Times New Roman;border:3px grey;border-radius:10px;padding-left: 2px;}"
                            "QLineEdit:focus {background-color: black;}");
    password->setEchoMode(QLineEdit::Password);

    logo=new QLabel(this);
    logo->setGeometry(400,60,150,150);
    QPixmap ku(":images/1.jpg");
    logo->setPixmap(ku);
    logo->setScaledContents(true);

    proceed=new QPushButton("Proceed",this);
    proceed->setGeometry(640,470,250,50);
    proceed->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border:3px grey;border-radius: 10px;font: 700 16pt Times New Roman;background-color: grey;}QPushButton:pressed{background-color: blue;}");

    icardsis=new QLabel(this);
    icardsis->setGeometry(640,60,250,150);
    QPixmap icard(":images/2.jpg");
    icardsis->setPixmap(icard);
    icardsis->setScaledContents(true);


    not_reg=new QLabel("Haven't registered yet?",this);
    not_reg->setStyleSheet("QLabel{ color: black;font:700 12pt Times New Roman;}");
    not_reg->setGeometry(635,540,300,50);

    get_regpage=new QPushButton("Register now!",this);
    get_regpage->setGeometry(805,540,100,40);
    get_regpage->setStyleSheet("QPushButton{color: rgb(82, 108, 255);font: 600 12pt Times New Roman;}QPushButton:pressed{background-color: rgb(0, 0, 200);}");

    person=new QLabel(this);
    person->setGeometry(893,355,25,30);
    QPixmap per(":images/user.jpg");
    person->setPixmap(per);
    person->setScaledContents(true);

    lock=new QLabel(this);
    lock->setGeometry(893,415,25,30);
    QPixmap lk(":images/hide.jpg");
    lock->setPixmap(lk);
    lock->setScaledContents(true);

    connect(proceed,&QPushButton::clicked,this,&MainWindow::on_proceed_clicked);
    connect(get_regpage,&QPushButton::clicked,this,&MainWindow::getregpage_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getregpage_clicked()
{
    reg=new regpage(this);
    reg->show();
}



void MainWindow::on_proceed_clicked()
{
    QString number=phone->text();
    std::string mobile_number = number.toStdString();
    QString pass=password->text();
    std::string password = pass.toStdString();
    std::string hashedPassword = generatecrypt(password);
    if (verifyLogin(mobile_number,hashedPassword))
    {
        int studentId = getStudentIdFromPhoneNumber(mobile_number);
        if (studentId != -1) {
            //std::cout << "Student ID: " << studentId << std::endl;
            hide();
            home=new homepage(studentId, this);
            home->show();
        } else {
            std::cout << "No student ID found for the given phone number." << std::endl;
            showError("ERROR!");
        }



    }
    else{
        // QMessageBox msgBox;
        // msgBox.setIcon(QMessageBox::Critical);
        // msgBox.setWindowTitle("Login Error");
        // msgBox.setText("INCORRECT INPUT OR FORGOT TO REGISTER?");
        // msgBox.setStyleSheet("QLabel{ color: black; }"
        //                      "QPushButton{ color: black; background-color: white; border: 1px solid black; }"
        //                      "QMessageBox{ background-color: white; }");
        // msgBox.exec();

    }


}



