#include <iostream>
#include <sstream>
#include <string>
#include "DatabaseModel.h"
#include "DatabaseHelper.h"

using namespace std;

//splitting the fullname
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

void addData(DatabaseHelper& dbHelper) {
    int id;
    string fullName, firstName, middleName, lastName, dob, bloodGroup, email, course;
    int yearOfEnrollment;

    // User input
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(); // To ignore newline character after entering ID

    cout << "Enter Full Name: ";
    getline(cin, fullName);

    splitFullName(fullName, firstName, middleName, lastName);

    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    getline(cin, dob);

    cout << "Enter Blood Group: ";
    getline(cin, bloodGroup);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Course: ";
    getline(cin, course);

    cout << "Enter Year of Enrollment: ";
    cin >> yearOfEnrollment;

    // Dynamic imgpath based on ID
    string imgpath = "imagepath/" + to_string(id) + ".jpg";

    DatabaseModel student(id, firstName, middleName, lastName, dob, bloodGroup, email, course, yearOfEnrollment, imgpath);

    if (dbHelper.idExists(student.id)) {
        cerr << "Error: ID " << student.id << " already exists." << endl;
    } else {
        dbHelper.insertData(student);
    }
}