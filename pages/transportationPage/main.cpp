#include <iostream>
#include "showStatus.h"

int main() {
    int studentId;

    std::cout << "Enter student ID: ";
    std::cin >> studentId;

    // Call the function to show the log
    TransportationStatus(studentId);

    return 0;
}