#include <iostream>
#include "A:\iCardSIS\vendors\sqlite\sqlite3.h"
#include <ctime>
#include <iomanip>
#include <sstream>

#include "A:\iCardSIS\pages\auditLogPage\auditInput.h"
// Function to get the current date in YYYY-MM-DD format
std::string CurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    std::ostringstream oss;
    oss << 1900 + ltm->tm_year << "-"
        << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "-"
        << std::setw(2) << std::setfill('0') << ltm->tm_mday;
    
    return oss.str();
}

// Function to calculate the difference in days between two dates
int dateDifference(const std::string& start_date, const std::string& end_date) {
    std::tm tm_start = {}, tm_end = {};
    std::istringstream ss_start(start_date);
    std::istringstream ss_end(end_date);
    
    ss_start >> std::get_time(&tm_start, "%Y-%m-%d");
    ss_end >> std::get_time(&tm_end, "%Y-%m-%d");
    
    auto time_start = std::mktime(&tm_start);
    auto time_end = std::mktime(&tm_end);
    
    const int seconds_in_day = 60 * 60 * 24;
    return std::difftime(time_end, time_start) / seconds_in_day;
}

bool finecalculator() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* db_name = "A:/iCardSIS/databases/library-database/library.db";
    const char* sql_query = "SELECT studentId, Deadline, days_dued, bookName FROM Books";
    
    // Open the SQLite database
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    
    // Prepare the SQL query
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    
    std::string current_date = CurrentDate();
    std::cout << "Current date: " << current_date << std::endl;
    
    // Execute the query and calculate fines
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int studentId = sqlite3_column_int(stmt, 0);
        const unsigned char* deadline = sqlite3_column_text(stmt, 1);
        std::string deadline_str(reinterpret_cast<const char*>(deadline));
        
        int days_dued = sqlite3_column_int(stmt, 2);
        
        int days_overdue = dateDifference(deadline_str, current_date);
        int new_overdue_days = days_overdue - days_dued;
        
        if (new_overdue_days > 0) {
            int fine = new_overdue_days * 10;

            // Update the fine for the student in the Borrowers table
            std::string update_fine_sql = "UPDATE Borrowers SET fine = fine + ? WHERE studentId = ?";
            sqlite3_stmt* update_stmt;
            if (sqlite3_prepare_v2(db, update_fine_sql.c_str(), -1, &update_stmt, 0) != SQLITE_OK) {
                std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }

            sqlite3_bind_int(update_stmt, 1, fine);
            sqlite3_bind_int(update_stmt, 2, studentId);

            if (sqlite3_step(update_stmt) != SQLITE_DONE) {
                std::cerr << "Failed to update fine: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(update_stmt);
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }

            sqlite3_finalize(update_stmt);

            // Update the days_dued for the book in the Borrowed_books table
            std::string update_days_dued_sql = "UPDATE Books SET days_dued = ? WHERE studentId = ? AND Deadline = ?";
            sqlite3_stmt* update_days_stmt;
            if (sqlite3_prepare_v2(db, update_days_dued_sql.c_str(), -1, &update_days_stmt, 0) != SQLITE_OK) {
                std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }

            sqlite3_bind_int(update_days_stmt, 1, days_overdue);
            sqlite3_bind_int(update_days_stmt, 2, studentId);
            sqlite3_bind_text(update_days_stmt, 3, deadline_str.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(update_days_stmt) != SQLITE_DONE) {
                std::cerr << "Failed to update days_dued: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(update_days_stmt);
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }
            

            sqlite3_finalize(update_days_stmt);

            const unsigned char* bookName = sqlite3_column_text(stmt, 3);
            std :: string book_name(reinterpret_cast<const char*>(bookName));

            std :: string text = "Added fine of " + std :: to_string(fine) + " for " + book_name + ".";
            insertActivity(studentId,text);
        }
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Fines and overdue days have been updated successfully." << std::endl;

    return 0;
}
