#include <iostream>
#include <string>
#include "showLog.h"

int main() {
    int studentId;

    std::cout << "Enter student ID: ";
    std::cin >> studentId;

    // Call the function to show the log
    showLog(studentId);

    return 0;
}