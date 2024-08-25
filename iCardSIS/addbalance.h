#ifndef ADDBALANCE_H
#define ADDBALANCE_H

#include <QDialog>
#include "vendors/sqlite/sqlite3.h"

namespace Ui {
class addbalance;
}

class addbalance : public QDialog
{
    Q_OBJECT

public:
    explicit addbalance(int id, sqlite3* db, QWidget *parent = nullptr);
    std::string phoneNumber,money2;
    int amount;
    sqlite3* dbx;
    int idxx;
    ~addbalance();
signals:
    void goback_from_addbalance();
private slots:
    void on_pushButton_addbalance_clicked();

    void on_pushButton_clicked();

private:
    Ui::addbalance *ui;
};
#endif // ADDBALANCE_H
