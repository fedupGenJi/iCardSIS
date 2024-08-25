#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QMainWindow>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include<addpage.h>
#include<fourthpage.h>
namespace Ui {
class secondpage;
}

class secondpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondpage(int id,QWidget *parent = nullptr);
    ~secondpage();
    int studentid;
private slots:

    void onExit();
    void onadd();
    void onRemove();


private:
    Ui::secondpage *ui;
    QLabel *label_1;
    QLabel *label_id, *label_stud;
    QLabel *logo_1;
    QLabel *choose;
    QPushButton *add;
    QPushButton *remove;
    QPushButton *exit;

    addpage *p3;
    fourthpage *p4;


};

#endif // SECONDPAGE_H
