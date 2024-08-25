#ifndef PHONENID_H
#define PHONENID_H
#include "sqlite/sqlite3.h"
#include <iostream>

int executeSQL(sqlite3* db, const std::string& sql);
bool gmailExists(sqlite3* db, const std::string& gmail);
void combineDatabases(const std::string& db1Path, const std::string& db2Path);

#endif // PHONENID_H
