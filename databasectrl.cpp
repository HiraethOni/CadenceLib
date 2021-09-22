#include "databasectrl.h"
#include "configctrl.h"
#include "XLogger.h"
#include <QDebug>
#include <QVariantMap>
#include <QVariantList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>

QSqlDatabase CDatabaseCtrl::sm_db = QSqlDatabase::addDatabase("QODBC");
CDatabaseCtrl::CDatabaseCtrl(QObject *parent) : QObject(parent)
{
    __m_table_column_name << "ID" << "Part Number" << "Description" << "Part Type" << "Value" << "MFG Name" << "PCB Footprint" << "Symbol" << "MFG Part Name"
        <<"MFG Part Description"<<"RoHS"<<"MFG Part Lifecycle Phase"<<"Datasheet"<<"buy link";
    __m_p_query = new QSqlQuery(sm_db);
    this->__ConnectDB();
}

bool CDatabaseCtrl::__ConnectDB() {
    CConfigDatabase conf_db;
    QStringList db_info = conf_db.ReadDatabase();

    sm_db.setHostName(db_info[0]);
    sm_db.setUserName(db_info[1]);
    sm_db.setPassword(db_info[2]);
    sm_db.setPort(db_info[3].toInt());
    sm_db.setDatabaseName(db_info[4]);
    bool status = sm_db.open();
    if (status){
        XLOG_INFO("Database opened successfully");
        return true;
    }
    XLOG_WARN("Database opened failed");
    return false;
}

QStringList CDatabaseCtrl::GetAllTablesNames() const {
    return this->sm_db.tables();
}

QString CDatabaseCtrl::GetAllContent(const QString tables_name) const {
    __m_p_query->exec("Select * from " + tables_name);
    QStringList str_list;

    // 返回的json前面加入一行空行,防止数据库是空的导致前端json解码失败
    // 同时也为了方便前端的表格新建这一功能的实现
    QVariantList qvarList;
    QVariantMap tmpVm;

    for (int i = 0; i < __m_table_column_name.count(); i++){
        tmpVm[__m_table_column_name[i]] = "";
    }
    qvarList<<tmpVm;
    
    while(__m_p_query->next()){
        tmpVm.clear();
        tmpVm[__m_table_column_name[0]] = QString::number(__m_p_query->value(0).toInt());
        for (int i = 1; i < __m_table_column_name.count(); i++){
            tmpVm[__m_table_column_name[i]] = __m_p_query->value(i).toString();
        }
        qvarList<<tmpVm;
    }

    QJsonArray jsonArray = QJsonArray::fromVariantList(qvarList);
    QJsonDocument jsonDoc(jsonArray);

    return jsonDoc.toJson();
}

QStringList CDatabaseCtrl::ScanPackageDir() const {
    CConfigCtrl conf;
    QString packagePath = conf.ReadInit("Allegro Footprints", "path");

    QDir dir(packagePath);
    QStringList nameFilters;
    nameFilters << "*.dra";

    QStringList rawName = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QStringList fileNameList;

    foreach(QString item, rawName){
        QStringList str_split = item.split('.');
        fileNameList.append(str_split[0]);
    }

    return fileNameList;
}
