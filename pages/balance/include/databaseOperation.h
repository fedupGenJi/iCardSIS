#pragma once
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

bool checkStudentId(sqlite3 *db, int studentId);
double getBalance(sqlite3 *db, int studentId);
bool updateBalance(sqlite3 *db, int studentId, int amount);
