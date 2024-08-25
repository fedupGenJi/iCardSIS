#ifndef KUTOAUDIT_HPP
#define KUTOAUDIT_HPP

#include "sqlite/sqlite3.h"
#include <vector>
#include <iostream>

std::vector<int> getStudentIds(sqlite3* db);
void createStudentActivityTables(const std::vector<int>& studentIds);
bool tableExists(sqlite3* db, const std::string& tableName);


#endif // KUTOAUDIT_HPP
