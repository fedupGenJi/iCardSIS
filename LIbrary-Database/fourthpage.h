#ifndef FOURTHPAGE_H
#define FOURTHPAGE_H

#include <QDialog>
#include<QPixmap>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
namespace Ui {
class fourthpage;
}

class fourthpage : public QDialog
{
    Q_OBJECT

public:
    explicit fourthpage(int id,QWidget *parent = nullptr);
    ~fourthpage();
    int student_id;
private slots:
    void on_confirm();
private:
    Ui::fourthpage *ui;
    QLabel *label_3;
    QLabel *logo_3;
    QLineEdit *book_id_1;
    QPushButton *confirm;
    QLabel *label_id;

};

#endif // FOURTHPAGE_H
