#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <string>

class DatabaseModel {
public:
    int id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string dob;
    std::string bloodGroup;
    std::string email;
    std::string course;
    int yearOfEnrollment;
    std::string imgpath;

    DatabaseModel(int id, const std::string& firstName, const std::string& middleName, const std::string& lastName, const std::string& dob, const std::string& bloodGroup, const std::string& email, const std::string& course, int yearOfEnrollment, const std::string& imgpath)
        : id(id), firstName(firstName), middleName(middleName), lastName(lastName), dob(dob), bloodGroup(bloodGroup), email(email), course(course), yearOfEnrollment(yearOfEnrollment), imgpath(imgpath) {}
};

#endif // DATABASEMODEL_H