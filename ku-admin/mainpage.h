#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

#include<addtoku.h>
#include<updatedb.h>
#include<reg_admin.h>
#include<canteen.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Mainpage;
}
QT_END_NAMESPACE

class Mainpage : public QMainWindow
{
    Q_OBJECT

public:
    Mainpage(QWidget *parent = nullptr);
    ~Mainpage();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_reg_clicked();

    void on_pushButton_canteen_clicked();

    void returnback_from_add();

    void returnback_from_update();

    void returnback_from_admin();

    void returnback_from_canteen();


private:
    Ui::Mainpage *ui;
    addtoku *addku;
    updatedb *upd;
    reg_admin *adm;
    canteen *can;

};
#endif // MAINPAGE_H
