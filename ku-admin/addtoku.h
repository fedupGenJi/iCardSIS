#ifndef ADDTOKU_H
#define ADDTOKU_H

#include <QMainWindow>
#include<data_addpage.h>
#include<data_removepage.h>

namespace Ui {
class addtoku;
}

class addtoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit addtoku(QWidget *parent = nullptr);
    ~addtoku();

signals:
    void goback_from_add();
private slots:
    void on_pushButton_add_1_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_back_clicked();
    void returnback_from_rem();
    void returnback_from_insert();

private:
    Ui::addtoku *ui;
    data_addpage *insert;
    data_removepage *rem;

};

#endif // ADDTOKU_H
