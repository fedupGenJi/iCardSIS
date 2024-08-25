#ifndef UPDATEDB_H
#define UPDATEDB_H

#include <QMainWindow>

namespace Ui {
class updatedb;
}

class updatedb : public QMainWindow
{
    Q_OBJECT

public:
    explicit updatedb(QWidget *parent = nullptr);
    ~updatedb();

private slots:
    void on_pushButton_back_2_clicked();

    void on_pushButton_bus_clicked();

    void on_pushButton_lib_clicked();

    void on_pushButton_phone_clicked();

    void on_pushButton_transport_clicked();

    void on_pushButton_audit_clicked();

signals:
    void goback_from_update();
private:
    Ui::updatedb *ui;
};

#endif // UPDATEDB_H
