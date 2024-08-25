#ifndef STUDENT_INFO_H
#define STUDENT_INFO_H

#include <string>

// Define the StudentInfo struct
struct StudentInfo {
    std::string fullName;
    std::string dateOfBirth;
    std::string course;
    int enrollmentYear;
    std::string bloodGroup;
    std::string photoPath;
};

// Declare the getStudentInfo function
StudentInfo getStudentInfo(int studentId);
#endif // STUDENT_INFO_H
