#include <iostream>
#include "LibManager.hpp"
#include "Book.hpp"

int main() {
    std::string dbPath = "library.db"; // Path to your SQLite database file
    LibManager libManager(dbPath);

    int studentID;
    std::cout << "Enter student ID: ";
    std::cin >> studentID;

    // Check if student ID exists in the database
    if (!libManager.checkStudentID(studentID)) {
        std::cerr << "Error: Student ID " << studentID << " does not exist in the database." << std::endl;
        return 1;
    }

    char choice;
    std::string bookID, bookName;

    while (true) {
        std::cout << "Choose operation:" << std::endl;
        std::cout << "1. Add book (enter 'A')" << std::endl;
        std::cout << "2. Remove book (enter 'R')" << std::endl;
        std::cout << "3. Exit (enter 'E')" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 'A':
                std::cout << "Enter book ID: ";
                std::cin >> bookID;
                std::cout << "Enter book name: ";
                std::cin.ignore(); // Clear input buffer
                std::getline(std::cin, bookName);

                libManager.addBook(studentID, bookID, bookName);
                break;
            case 'R':
                std::cout << "Enter book ID to remove: ";
                std::cin >> bookID;

                libManager.removeBook(studentID, bookID);
                break;
            case 'E':
                std::cout << "Exiting program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    }

    return 0;
}