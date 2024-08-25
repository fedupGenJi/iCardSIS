#ifndef TRANSFERBALANCE_H
#define TRANSFERBALANCE_H

#include <QDialog>
#include "vendors/sqlite/sqlite3.h"
namespace Ui {
class transferbalance;
}

class transferbalance : public QDialog
{
    Q_OBJECT

public:
    explicit transferbalance(int idxx, sqlite3* db,QWidget *parent = nullptr);
    std::string receipentNumber,money;
    int amount;
    sqlite3* dbx;
    int idxx;
    ~transferbalance();

signals:
    void goback_from_transferbalance();
private slots:
    void on_pushButton_addbalance_clicked();

    void on_pushButton_clicked();

private:
    Ui::transferbalance *ui;
};

#endif // TRANSFERBALANCE_H
