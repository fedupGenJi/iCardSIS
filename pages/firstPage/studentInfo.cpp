#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include "studentInfo.h"

StudentInfo getStudentInfo(int studentId) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    StudentInfo studentInfo;

    // Open the SQLite database
    rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return studentInfo;
    }

    // Prepare the SQL statement
    std::string sql = "SELECT firstName, middleName, lastName, dob, course, yearOfEnrollment, bloodGroup, imgpath FROM studentID WHERE id = ?";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return studentInfo;
    }

    // Bind the student ID to the statement
    rc = sqlite3_bind_int(stmt, 1, studentId);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind student ID: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return studentInfo;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::string firstName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string middleName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string lastName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        
        studentInfo.fullName = firstName + " " + middleName + " " + lastName;
        studentInfo.dateOfBirth = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        studentInfo.course = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        studentInfo.enrollmentYear = sqlite3_column_int(stmt, 5);
        studentInfo.bloodGroup = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        studentInfo.photoPath = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
    } else if (rc == SQLITE_DONE) {
        std::cerr << "Student ID not found." << std::endl;
    } else {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return studentInfo;
};

void firstPage(int studentId) {

    StudentInfo studentInfo = getStudentInfo(studentId);
    if (!studentInfo.fullName.empty()) {
        std::cout << "Full Name: " << studentInfo.fullName << std::endl;
        std::cout << "Date of Birth: " << studentInfo.dateOfBirth << std::endl;
        std::cout << "Course: " << studentInfo.course << std::endl;
        std::cout << "Enrollment Year: " << studentInfo.enrollmentYear << std::endl;
        std::cout << "Blood Group: " << studentInfo.bloodGroup << std::endl;
        std::cout << "Photo Path: " << studentInfo.photoPath << std::endl;
    } else {
        std::cout << "Error!" << std::endl;
    }
}