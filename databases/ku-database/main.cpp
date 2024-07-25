#include <iostream>
#include "DatabaseHelper.h"
#include "add.cpp"

using namespace std;

void addData(DatabaseHelper& dbHelper);
void deleteData(DatabaseHelper& dbHelper);

int main() {
    DatabaseHelper dbHelper("ku-database.db");//use studentData for the main database
    dbHelper.createTable();
    int choice;
    while (true) {
        cout << "Choose an option:\n1. Add data\n2. Delete data\n3. Exit\n";
        cin >> choice;
        cin.ignore(); // To ignore newline character after entering choice

        if (choice == 1) {
            
            addData(dbHelper);
        } else if (choice == 2) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;

            dbHelper.deleteData(id);
        } else if (choice == 3) {
            break;
        } else {
            cerr << "Invalid choice" << endl;
        }
    }

    return 0;
}

void deleteData(DatabaseHelper& dbHelper) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    dbHelper.deleteData(id);
}