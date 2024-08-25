#include "payfine.h"
#include "ui_payfine.h"
#include<iostream>
#include "string"
using namespace std;
#include <QMessageBox>
#include "QString"
#include "include/databaseOperation.h"
#include "auditInput.h"

void Errormsgggg(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
void Successmsggggg(const QString &message){
    QMessageBox::information(nullptr,"Sucess!",message);
}


payFine::payFine(int studentIdx,sqlite3* dbx, sqlite3* finesDbx, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::payFine)
{

    ui->setupUi(this);
    studentId = studentIdx;
    db = dbx;
    finesDb = finesDbx;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT fine FROM Borrowers WHERE studentID = ?";
    if (sqlite3_prepare_v2(finesDb, sql, -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(finesDb) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        currentFine = sqlite3_column_double(stmt, 0);
    }

    else
    {
        Errormsgggg("Failure in operation!");
        emit goback_from_fine();
    }

    sqlite3_finalize(stmt);

    QString xx = QString::fromStdString(to_string(currentFine));
    ui->fineAmount->setText(xx);
}

payFine::~payFine()
{
    delete ui;
}

void payFine::on_payButton_clicked()
{
    QString x = ui->toPay->text();
    if(x.QString::isEmpty())
    {
        Errormsgggg("Write amount to pay!");
        emit goback_from_fine();
    }
    else
    {
        string xxx = x.toStdString();
        fineAmount = stoi(xxx);
        int balance = getBalance(db, studentId);
        if (balance < fineAmount) {
            //cerr << "Insufficient balance to pay the fine!" << endl;
            Errormsgggg("Insufficient balance to pay the fine!");
            emit goback_from_fine();
        }
        else{
            sqlite3_stmt *stmt;
            const char* sql = "UPDATE Borrowers SET fine = fine - ? WHERE studentID = ?";
            if (sqlite3_prepare_v2(finesDb, sql, -1, &stmt, 0) != SQLITE_OK) {
                //cerr << "Failed to prepare statement: " << sqlite3_errmsg(finesDb) << endl;
                //return;
                Errormsgggg("ERROR!");
                emit goback_from_fine();

            }

            sqlite3_bind_double(stmt, 1, fineAmount);
            sqlite3_bind_int(stmt, 2, studentId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                //cerr << "Failed to update fine amount: " << sqlite3_errmsg(finesDb) << endl;
                sqlite3_finalize(stmt);
                Errormsgggg("ERROR!");
                emit goback_from_fine();
                //return;
            }

            sqlite3_finalize(stmt);

            if (updateBalance(db, studentId, -fineAmount)) {
                cout << "Fine paid successfully!" << endl;
                Successmsggggg("Fine paid!");
                string textmsg = "Paid Fine of " + to_string(fineAmount) +".";
                insertActivity(studentId,textmsg);
            }
            emit goback_from_fine();
        }
    }
}


void payFine::on_pushButton_clicked()
{
    emit goback_from_fine();
}

