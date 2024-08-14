#pragma once
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include<string>

std::string getDate();
std::string getDeadlineDate();
void bus_Subscription(sqlite3 *db, int studentId);
void displayRoute(sqlite3* db, int studentId);
void updateTransportation(sqlite3* db, int studentId, int choice);
void checkForTable(sqlite3* db, int studentId);