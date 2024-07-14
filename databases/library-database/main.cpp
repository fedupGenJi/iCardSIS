#include <iostream>
#include "LibManager.hpp"
#include <regex>
#include <sstream>
#include <ctime>

// Display operations menu
void displayMenu() {
    std::cout << "1. Add book" << std::endl;
    std::cout << "2. Remove book" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter choice: ";
}

// Validate date format (YYYY-MM-DD)
bool isValidDate(const std::string& date) {
    std::regex datePattern(R"((\d{4})-(\d{2})-(\d{2}))");
    std::smatch match;
    if (std::regex_match(date, match, datePattern)) {
        int year = std::stoi(match[1].str());
        int month = std::stoi(match[2].str());
        int day = std::stoi(match[3].str());

        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        std::tm time_in = { 0, 0, 0, day, month - 1, year - 1900 };
        std::time_t time_temp = std::mktime(&time_in);

        const std::tm *time_out = std::localtime(&time_temp);

        return (time_out->tm_year == time_in.tm_year
            && time_out->tm_mon == time_in.tm_mon
            && time_out->tm_mday == time_in.tm_mday);
    }
    return false;
}

// Get valid date input
std::string getValidDateInput(const std::string& prompt) {
    std::string date;
    while (true) {
        std::cout << prompt;
        std::cin >> date;
        if (isValidDate(date)) {
            break;
        }
        std::cout << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
    }
    return date;
}

int main() {
    LibManager libManager("library.db");

    int studentID;
    std::cout << "Enter student ID: ";
    std::cin >> studentID;

    // Check if student ID exists in the Borrowers table
    if (!libManager.checkBorrower(studentID)) {
        std::cerr << "Error: No such user ID found." << std::endl;
        return 1;
    }

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string bookID, bookName, submissionDate;
                std::cout << "Enter book ID: ";
                std::cin >> bookID;
                std::cout << "Enter book name: ";
                std::cin.ignore();
                std::getline(std::cin, bookName);
                submissionDate = getValidDateInput("Enter submission date (YYYY-MM-DD): ");

                libManager.addBook(studentID, bookID, bookName, submissionDate);
                std::cout << "Book added successfully." << std::endl;
                break;
            }
            case 2: {
                std::string bookID;
                std::cout << "Enter book ID: ";
                std::cin >> bookID;

                libManager.removeBook(studentID, bookID);
                break;
            }
            case 3:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 3);

    return 0;
}