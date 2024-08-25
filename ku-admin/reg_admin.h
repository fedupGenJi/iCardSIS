#ifndef REG_ADMIN_H
#define REG_ADMIN_H

#include <QMainWindow>
#include<remove_regpage.h>
#include<change_num.h>
namespace Ui {
class reg_admin;
}

class reg_admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit reg_admin(QWidget *parent = nullptr);
    ~reg_admin();

private slots:
    void on_pushButton_regremove_clicked();
    void on_pushButton_back_3_clicked();

    void returnback_from_1();
    void returnback_from_2();

    void on_pushButton_change_clicked();

signals:
    void goback_from_admin();
private:
    Ui::reg_admin *ui;
    remove_regpage *remp;
    change_num *num;
};

#endif // REG_ADMIN_H
