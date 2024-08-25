#pragma once
#include "vendors/sqlite/sqlite3.h"
#include <string>
using namespace std;

bool addBalances(sqlite3 *db, int studentId, string phoneNumber, int amount);
bool transferBalance(sqlite3 *db, int studentId, string recipientPhoneNumber, int amount);
