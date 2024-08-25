#pragma once
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include<string>

std::string getDate();
std::string getDeadlineDate();
bool bus_Subscription(sqlite3 *db, int studentId);
//void displayRoute(sqlite3* db, int studentId);
bool updateTransportation(sqlite3* db, int studentId, int choice);
bool checkForTable(sqlite3* db, int studentId, int choice);
