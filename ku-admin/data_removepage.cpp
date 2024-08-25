#include "data_removepage.h"
#include "ui_data_removepage.h"
#include "DatabaseHelper.h"

data_removepage::data_removepage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::data_removepage)
{
    ui->setupUi(this);
}

data_removepage::~data_removepage()
{
    delete ui;
}

void data_removepage::on_pushButton_delete_clicked()
{
    DatabaseHelper dbHelper("A:\\iCardSIS\\databases\\ku-database\\ku-database.db");//use studentData for the main database
    dbHelper.createTable();
    QString idx = ui->lineEdit_idRemove->text();
    std::string id = idx.toStdString();
    dbHelper.deleteData(std::stoi(id));

    emit goback_from_rem();
}

