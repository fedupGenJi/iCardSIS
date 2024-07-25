#include <iostream>
#include "CopyDatabase.hpp"

int main() {
    // Provide the full paths to your databases
    std::string sourceDbPath = "A:\\iCardSIS\\databases\\ku-database\\example.db";
    std::string targetDbPath = "A:\\iCardSIS\\databases\\balance\\balance.db"; 
    std::string sourceTable = "studentID"; // Source table name with IDs
    std::string targetTable = "Student"; // Target table name with studentID column

    // Open source database and get IDs
    CopyDatabase sourceDb(sourceDbPath);
    sourceDb.displayTable(sourceTable); // Display contents of the source table
    std::vector<int> ids = sourceDb.getIDs(sourceTable);

    // Open target database and insert IDs
    CopyDatabase targetDb(targetDbPath);
    targetDb.insertIDs(targetTable, ids);
    targetDb.displayTable(targetTable); // Display contents of the target table

    return 0;
}