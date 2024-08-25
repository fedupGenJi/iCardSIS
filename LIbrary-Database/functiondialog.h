#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QDialog>

namespace Ui {
class functiondialog;
}

class functiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit functiondialog(QWidget *parent = nullptr);
    ~functiondialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::functiondialog *ui;
};

#endif // FUNCTIONDIALOG_H
