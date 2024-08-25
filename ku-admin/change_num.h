#ifndef CHANGE_NUM_H
#define CHANGE_NUM_H

#include <QDialog>

namespace Ui {
class change_num;
}

class change_num : public QDialog
{
    Q_OBJECT

public:
    explicit change_num(QWidget *parent = nullptr);
    ~change_num();
signals:
    void goback_from_22();
private slots:
    void on_pushButton_change_clicked();

private:
    Ui::change_num *ui;
};

#endif // CHANGE_NUM_H
