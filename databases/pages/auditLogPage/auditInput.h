#ifndef ACTIVITY_LOGGER_H
#define ACTIVITY_LOGGER_H

#include <string>

std::string getCurrentDate();
void insertActivity(int studentId, const std::string& activity);

#endif // ACTIVITY_LOGGER_H