#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include<balance.h>
#include<activity.h>
#include<books.h>
#include<transportation.h>
namespace Ui {
class homepage;
}

class homepage : public QMainWindow
{
    Q_OBJECT

public:
    QString imagePath;
    int studentId;
    explicit homepage(int id, QWidget *parent = nullptr);
    ~homepage();

private slots:


    void on_pushButton_exit_clicked();

    void on_pushButton_balance_clicked();

    void on_pushButton_library_clicked();

    void on_pushButton_transport_clicked();

    void on_pushButton_activity_clicked();

private:
    Ui::homepage *ui;
    balance *bal;
    books *bks;
    activity *act;
    transportation *transport;

};

#endif // HOMEPAGE_H
