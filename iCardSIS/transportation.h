#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <QMainWindow>

namespace Ui {
class transportation;
}

class transportation : public QMainWindow
{
    Q_OBJECT

public:
    explicit transportation(int id, QString x,QWidget *parent = nullptr);
    ~transportation();

private:
    Ui::transportation *ui;
};

#endif // TRANSPORTATION_H
