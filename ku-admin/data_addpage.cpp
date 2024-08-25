#include "data_addpage.h"
#include "ui_data_addpage.h"
#include <sstream>
#include <string>
#include "DatabaseModel.h"
#include "DatabaseHelper.h"
using namespace std;
data_addpage::data_addpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_addpage)
{
    ui->setupUi(this);
}

void splitFullName(const string& fullName, string& firstName, string& middleName, string& lastName) {
    stringstream ss(fullName);
    getline(ss, firstName, ' ');
    getline(ss, middleName, ' ');
    getline(ss, lastName);

    if (middleName.empty()) {
        lastName = firstName;
        firstName = "";
    }
    if (lastName.empty()) {
        lastName = middleName;
        middleName = "";
    }
}

data_addpage::~data_addpage()
{
    delete ui;
}

//on add clicked check and show message(error/success) and hide this dialog if success

void data_addpage::on_pushButton_conti_1_clicked()
{
    DatabaseHelper dbHelper("A:\\iCardSIS\\databases\\ku-database\\ku-database.db");
    dbHelper.createTable();

    QString name = ui->lineEdit_fullname->text();
    QString idx = ui->lineEdit_id->text();
    QString dobx = ui->lineEdit_dob->text();
    QString mailx = ui->lineEdit_eamil->text();
    QString bgx= ui->lineEdit_blood->text();
    QString coursex = ui->lineEdit_course->text();
    QString yearx= ui->lineEdit_year->text();

    int id;
    string fullName, firstName, middleName, lastName, dob, bloodGroup, email, course;
    int yearOfEnrollment;

    fullName = name.toStdString();
    splitFullName(fullName, firstName, middleName, lastName);

    dob = dobx.toStdString();
    bloodGroup = bgx.toStdString();
    email = mailx.toStdString();
    course = coursex.toStdString();

    string idxx = idx.toStdString();
    id = stoi(idxx);
    string year = yearx.toStdString();
    yearOfEnrollment = stoi(year);

    string imgpath = "imagepath/" + to_string(id) + ".jpg";

    DatabaseModel student(id, firstName, middleName, lastName, dob, bloodGroup, email, course, yearOfEnrollment, imgpath);

    if (dbHelper.idExists(student.id)) {
        cerr << "Error: ID " << student.id << " already exists." << endl;
        dbHelper.Errormessage("Student id already exists!");
    } else {
        dbHelper.insertData(student);
    }

    emit goback_from_insert();
}

