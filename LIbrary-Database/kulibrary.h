#ifndef KULIBRARY_H
#define KULIBRARY_H
#include<QLabel>
#include<QWidget>
#include<QPushButton>
#include <QMainWindow>
#include<QPixmap>
#include<QLineEdit>
#include<QMessageBox>
#include<secondpage.h>
#include<functiondialog.h>
#include<iostream>
QT_BEGIN_NAMESPACE
namespace Ui {
class KULibrary;
}
QT_END_NAMESPACE

class KULibrary : public QMainWindow
{
    Q_OBJECT

public:
    KULibrary(QWidget *parent = nullptr);
    ~KULibrary();
private slots:
    void openSecondPage();
    void call_function();


private:
    Ui::KULibrary *ui;
    QLabel *label;
    QPushButton *button;
    QPushButton *function_button;
    QLineEdit *student_id;
    QLabel *logo;
    secondpage *page_2;
    functiondialog *dialog;




};
#endif // KULIBRARY_H
