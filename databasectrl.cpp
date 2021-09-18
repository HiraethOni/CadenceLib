#include "databasectrl.h"
#include "configctrl.h"
#include <QDebug>

QSqlDatabase databaseCtrl::db = QSqlDatabase::addDatabase("QODBC");
databaseCtrl::databaseCtrl(QObject *parent) : QObject(parent)
{
    table_column_name<<"ID"<<"Part Number"<<"Description"<<"Part Type"<<"Value"<<"MFG Name"<<"PCB Footprint"<<"Symbol"<<"MFG Part Name"
        <<"MFG Part Description"<<"RoHS"<<"MFG Part Lifecycle Phase"<<"Datasheet"<<"buy link";
    p_query = new QSqlQuery(db);
    this->connectDB();
}

bool databaseCtrl::connectDB() {
    configDatabase conf_db;
    QStringList db_info = conf_db.readDatabase();

    db.setHostName(db_info[0]);
    db.setUserName(db_info[1]);
    db.setPassword(db_info[2]);
    db.setPort(db_info[3].toInt());
    db.setDatabaseName(db_info[4]);
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

QString databaseCtrl::getAllContent(const QString tables_name) const {
    p_query->exec("Select * from "+tables_name);
    QStringList str_list;
    while(p_query->next()){
        QStringList temp_list;
        temp_list << "\"" + table_column_name[0] + "\":\"" + QString::number(p_query->value(0).toInt()) + "\"";
        for (int i = 1; i < table_column_name.count(); i++){
            temp_list << "\"" + table_column_name[i] + "\":\"" + p_query->value(i).toString() + "\"";
        }
        str_list<<"{" + temp_list.join(",") + "}";
    }
    return "[" + str_list.join(",") + "]";
}
