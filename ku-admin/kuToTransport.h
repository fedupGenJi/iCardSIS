#ifndef KUTOTRANSPORT_H
#define KUTOTRANSPORT_H
#include "sqlite/sqlite3.h"
#include <vector>
#include <ctime>
#include <vector>
#include <string>

bool updateStatusAndDaysLeft(const std::vector<int>& ids, const std::string& dbPath);
std::tm parseDateTime(const std::string& dateTime);
std::string getCurrentTime();

#endif // KUTOTRANSPORT_H
