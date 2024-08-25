#ifndef CANTEEN_H
#define CANTEEN_H

#include <QMainWindow>

namespace Ui {
class canteen;
}

class canteen : public QMainWindow
{
    Q_OBJECT

public:
    explicit canteen(QWidget *parent = nullptr);
    ~canteen();
signals:
    void goback_from_canteen();
private slots:
    void on_pushButton_back_4_clicked();

    void on_pushButton_conti_clicked();

private:
    Ui::canteen *ui;
};

#endif // CANTEEN_H
