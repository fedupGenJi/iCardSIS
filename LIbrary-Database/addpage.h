#ifndef ADDPAGE_H
#define ADDPAGE_H

#include <QDialog>
#include<QPixmap>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include <QMessageBox>
namespace Ui {
class addpage;
}

class addpage : public QDialog
{
    Q_OBJECT

public:
    explicit addpage(int id,QWidget *parent = nullptr);
    ~addpage();
    int student_id;

private slots:
    void on_done();

private:
    Ui::addpage *ui;
    QLabel *label_2;
    QLabel *logo_2;
    QLabel *fill;
    QLineEdit *book_id;
    QLineEdit *book_name;
    QLineEdit *submission_date;
    QPushButton *done;
    QLabel *label_id;
};

#endif // ADDPAGE_H
