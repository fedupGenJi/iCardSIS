#include <iostream>
#include <string>
#include "showLibraryLog.h"

int main() {
    int studentId;

    std::cout << "Enter student ID: ";
    std::cin >> studentId;

    // Call the function to show the log
    showLibraryLog(studentId);

    return 0;
}