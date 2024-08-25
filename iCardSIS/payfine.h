#ifndef PAYFINE_H
#define PAYFINE_H

#include <QDialog>
#include "vendors/sqlite/sqlite3.h"
namespace Ui {
class payFine;
}

class payFine : public QDialog
{
    Q_OBJECT

public:
    explicit payFine(int studentId,sqlite3* db, sqlite3* finesDb, QWidget *parent = nullptr);
    ~payFine();
    int currentFine;
    int studentId;
    int fineAmount;
    sqlite3* db;
    sqlite3* finesDb;

private slots:
    void on_payButton_clicked();

    void on_pushButton_clicked();

signals:
    void goback_from_fine();
private:
    Ui::payFine *ui;
};

#endif // PAYFINE_H
