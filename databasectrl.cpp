#include "databasectrl.h"
#include "configctrl.h"
#include <qDebug>

databaseCtrl::databaseCtrl()
{
    this->connectDB();
}

bool databaseCtrl::connectDB() {
    configDatabase conf_db;
    QStringList db_info = conf_db.readDatabase();

    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName(db_info[0]);
    db.setPort(3306);
    db.setUserName(db_info[1]);
    db.setPassword(db_info[2]);
    db.setDatabaseName(db_info[3]);
    bool status = db.open();
    if (status){
        qDebug()<<"Database opened successfully";
        return true;
    }
    qDebug()<<"Database opened failed";
    return false;
}

QStringList databaseCtrl::getAllTablesNames() const {
    return this->db.tables();
}
