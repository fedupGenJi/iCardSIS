#pragma once
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

void addBalance(sqlite3 *db, int studentId);
void transferBalance(sqlite3 *db, int studentId);
