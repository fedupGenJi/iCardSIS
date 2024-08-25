#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<regpage.h>
#include<homepage.h>
#include<QMessageBox>
#include<QLabel>
#include<QWidget>
#include<QPushButton>
#include <QMainWindow>
#include<QPixmap>
#include<QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getregpage_clicked();

    void on_proceed_clicked();



private:
    Ui::MainWindow *ui;
    homepage *home;
    regpage *reg;
    QLabel *label;
    QPushButton *proceed;
    QPushButton *get_regpage;
    QLineEdit *phone,*password;
    QLabel *logo, *icardsis, *enter, *not_reg, *person, *lock;
};
#endif // MAINWINDOW_H
