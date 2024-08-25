#ifndef DATA_ADDPAGE_H
#define DATA_ADDPAGE_H

#include <QDialog>

namespace Ui {
class data_addpage;
}

class data_addpage : public QDialog
{
    Q_OBJECT

public:
    explicit data_addpage(QWidget *parent = nullptr);
    ~data_addpage();

private slots:
    void on_pushButton_conti_1_clicked();

signals:
    void goback_from_insert();

private:
    Ui::data_addpage *ui;
};

#endif // DATA_ADDPAGE_H
