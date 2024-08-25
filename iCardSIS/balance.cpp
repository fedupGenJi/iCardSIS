#include "balance.h"
#include "ui_balance.h"
#include <iostream>
#include "vendors/sqlite/sqlite3.h"
using namespace std;

int showBalance(sqlite3 *db, int studentId)
{
    sqlite3_stmt* stmt;
    const char* query = "SELECT balance FROM Balance WHERE studentId = ?";
    int balance = -1; // Initializing balance to -1 to indicate an error if not found

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return balance;
    }

    // Bind the studentId parameter to the SQL query
    if (sqlite3_bind_int(stmt, 1, studentId) != SQLITE_OK) {
        std::cerr << "Failed to bind studentId: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return balance;
    }

    // Execute the SQL query and retrieve the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balance = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "No balance found for studentId: " << studentId << std::endl;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return balance;
}

balance::balance(int id,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    studentId = id;
    //initialize databases

    int rc = sqlite3_open("A:\\iCardSIS\\databases\\ku-database\\ku-database.db", &db);
    if (rc) {
        cerr << "Can't open ku-database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    rc = sqlite3_open("A:\\iCardSIS\\databases\\library-database\\library.db", &finesDb);
    if (rc) {
        cerr << "Can't open fine database: " << sqlite3_errmsg(finesDb) << endl;
        sqlite3_close(db);
        return;
    }

    int balance = showBalance(db,studentId);

    ui->label_availBal->setText(QString:: fromStdString(to_string(balance)));
}

balance::~balance()
{
    delete ui;
}




void balance::on_pushButton_addbalance_clicked()
{
    addbal= new addbalance(studentId,db,this);
    connect(addbal,&addbalance::goback_from_addbalance,this,&balance::returnback_from_addbalance);
    addbal->show();
    this->hide();

}


void balance::on_pushButton_transferbalance_clicked()
{
    transferbal= new transferbalance(studentId,db,this);
    connect(transferbal,&transferbalance::goback_from_transferbalance,this,&balance::returnback_from_transferbalance);
    transferbal->show();
    this->hide();
}

void balance :: returnback_from_addbalance()
{
    updatePage();
    this->show();
    addbal->hide();
}


void balance :: returnback_from_transferbalance()
{
    updatePage();
    this->show();
    transferbal->hide();
}




void balance::on_pushButton__bus_clicked()
{
    sub= new subscription(studentId,db,this);
    connect(sub,&subscription::goback_from_subscription,this,&balance::returnback_from_subscription);
    sub->show();
    this->hide();
}

void balance :: returnback_from_subscription()
{
    updatePage();
    this->show();
    sub->hide();
}

void balance::on_payFine_clicked()
{
    fine = new payFine(studentId,db,finesDb,this);
    connect(fine,&payFine::goback_from_fine,this,&balance::returnback_from_fine);
    fine->show();
    this->hide();
}

void balance::returnback_from_fine()
{
    updatePage();
    this->show();
    fine->hide();
}

void balance::updatePage()
{
    int balance = showBalance(db,studentId);

    ui->label_availBal->setText(QString:: fromStdString(to_string(balance)));
}
