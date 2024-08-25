#pragma once
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"

void payFines(sqlite3 *finesDb, sqlite3 *db, int studentId);
