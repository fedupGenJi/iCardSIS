#include "thirdpage.h"
#include "ui_thirdpage.h"

thirdpage::thirdpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::thirdpage)
{
    ui->setupUi(this);
}

thirdpage::~thirdpage()
{
    delete ui;
}
