#ifndef REMOVE_REGPAGE_H
#define REMOVE_REGPAGE_H

#include <QDialog>

namespace Ui {
class remove_regpage;
}

class remove_regpage : public QDialog
{
    Q_OBJECT

public:
    explicit remove_regpage(QWidget *parent = nullptr);
    ~remove_regpage();

private slots:
    void on_pushButton_delete_1_clicked();

signals:
    void goback_from_11();

private:
    Ui::remove_regpage *ui;
};

#endif // REMOVE_REGPAGE_H
