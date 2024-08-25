#include "updatedb.h"
#include "ui_updatedb.h"
#include "CopyDatabase.hpp"
#include "kuToTransport.h"
#include "kuToAudit.hpp"
#include "phoneNId.h"
#include <QMessageBox>
updatedb::updatedb(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::updatedb)
{
    ui->setupUi(this);
}

updatedb::~updatedb()
{
    delete ui;
}
void Errormsg(const QString &errorMessage) {
    QMessageBox::critical(nullptr, "Error", errorMessage);
}
void Successmsg(const QString &message){
    QMessageBox::information(nullptr,"Sucess!",message);
}
//on the function buttons clicked check if success or failure

void updatedb::on_pushButton_back_2_clicked()
{
    emit goback_from_update();
}


void updatedb::on_pushButton_bus_clicked()
{
    // Provide the full paths to your databases
    std::string sourceDbPath = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    std::string targetDbPath = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    std::string sourceTable = "studentID"; // Source table name with IDs
    std::string targetTable = "Balance"; // Target table name with studentID column

    // Open source database and get IDs
    CopyDatabase sourceDb(sourceDbPath);
    //sourceDb.displayTable(sourceTable); // Display contents of the source table
    std::vector<int> ids = sourceDb.getIDs(sourceTable);

    // Open target database and insert IDs
    CopyDatabase targetDb(targetDbPath);
    targetDb.insertIDs(targetTable, ids);
    //targetDb.displayTable(targetTable); // Display contents of the target table
    Successmsg("Successfully binded the datas!");
    emit goback_from_update();
}


void updatedb::on_pushButton_lib_clicked()
{
    // Provide the full paths to your databases
    std::string sourceDbPath = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    std::string targetDbPath = "A:\\iCardSIS\\databases\\library-database\\library.db";
    std::string sourceTable = "studentID"; // Source table name with IDs
    std::string targetTable = "Borrowers"; // Target table name with studentID column

    // Open source database and get IDs
    CopyDatabase sourceDb(sourceDbPath);
    //sourceDb.displayTable(sourceTable); // Display contents of the source table
    std::vector<int> ids = sourceDb.getIDs(sourceTable);

    // Open target database and insert IDs
    CopyDatabase targetDb(targetDbPath);
    targetDb.insertIDs(targetTable, ids);
    //targetDb.displayTable(targetTable); // Display contents of the target table
    Successmsg("Successfully binded the datas!");
    emit goback_from_update();
}


void updatedb::on_pushButton_phone_clicked()
{
    const std::string db1Path = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    const std::string db2Path = "A:\\iCardSIS\\databases\\login-database\\registration.db";

    combineDatabases(db1Path, db2Path);
    Successmsg("Successfully binded the datas!");
    emit goback_from_update();

}




void updatedb::on_pushButton_transport_clicked()
{
    // Provide the full paths to your databases
    std::string sourceDbPath = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    std::string targetDbPath = "A:\\iCardSIS\\databases\\ku-database\\ku-database.db";
    std::string sourceTable = "studentID"; // Source table name with IDs
    std::string targetTable = "Transportation"; // Target table name with studentID column

    // Open source database and get IDs
    CopyDatabase sourceDb(sourceDbPath);
    //sourceDb.displayTable(sourceTable); // Display contents of the source table
    std::vector<int> ids = sourceDb.getIDs(sourceTable);

    // Open target database and insert IDs
    CopyDatabase targetDb(targetDbPath);
    targetDb.insertIDs(targetTable, ids);

    if(!updateStatusAndDaysLeft(ids,targetDbPath))
    {
        std::cerr<<"Could not update Transportation database!" << std::endl;
        Errormsg("Could not update Transportation Database!");
    }
    std::cout<<"Updated Tranportation database!"<< std::endl;
    //targetDb.displayTable(targetTable); // Display contents of the target table
    Successmsg("Successfully binded the datas!");
    emit goback_from_update();
}


void updatedb::on_pushButton_audit_clicked()
{
    sqlite3* db;
    int rc = sqlite3_open("A:/iCardSIS/databases/ku-database/ku-database.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        Errormsg("ERROR!");
    }

    std::vector<int> studentIds = getStudentIds(db);
    sqlite3_close(db);

    createStudentActivityTables(studentIds);

    Successmsg("Successfully binded the datas!");
    emit goback_from_update();
}

