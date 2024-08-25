#ifndef DATA_REMOVEPAGE_H
#define DATA_REMOVEPAGE_H

#include <QDialog>

namespace Ui {
class data_removepage;
}

class data_removepage : public QDialog
{
    Q_OBJECT

public:
    explicit data_removepage(QWidget *parent = nullptr);
    ~data_removepage();

signals:
    void goback_from_rem();
private slots:
    void on_pushButton_delete_clicked();

private:
    Ui::data_removepage *ui;
};

#endif // DATA_REMOVEPAGE_H
