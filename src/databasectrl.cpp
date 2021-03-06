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

QStringList CDatabaseCtrl::getAllTablesNames() const {
    return this->sm_db.tables();
}

QString CDatabaseCtrl::getAllContent(const QString tables_name) const {
    __m_p_query->exec("Select * from " + tables_name);

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

QStringList CDatabaseCtrl::scanPackageDir() const {
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

QStringList CDatabaseCtrl::getFiledValue(const QString field, const QString tables_name) const {
    QString queryStr = "Select `" + field + "` from " + tables_name;
    XLOG_TRACE("{}", queryStr.toStdString());
    __m_p_query->exec(queryStr);
    QStringList partType;
    while(__m_p_query->next()){
        QString partTypeVale = __m_p_query->value(0).toString();
        if (partType.contains(partTypeVale)) continue;
        partType<<partTypeVale;
#ifdef _DEBUG
        XLOG_TRACE("SQL query results:{}", partTypeVale.toStdString());
#endif
    }
    return partType;
}

bool CDatabaseCtrl::insertData(QString table_name, QStringList data) const {
    bool partNumber_isEmpty = data.first().isEmpty();
    /**
     * @note 这里必须添加单引号,不然sql语句无法执行
     */
    __AddApostrophe(data);
    QString insertValue = data.join(",");

    QStringList tmp_insertField = __m_table_column_name;
    tmp_insertField.removeFirst();
    /**
     * 这里添加反引号避免字段名内含有空格
     */
    __AddBackticks(tmp_insertField);
    QString insertFields = tmp_insertField.join(",");

    QString sql_insert = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(table_name).arg(insertFields).arg(insertValue);
    XLOG_INFO("Insert query: {}", sql_insert.toStdString());
    bool query_status = __m_p_query->exec(sql_insert);

    if (partNumber_isEmpty && query_status) {
        XLOG_TRACE("Not defined Part Number");
        query_status = __m_p_query->exec("SELECT LAST_INSERT_ID();");
        __m_p_query->next();
        int id = __m_p_query->value(0).toInt();
        XLOG_TRACE("Last insert id: {}", id);
        query_status = __m_p_query->exec(QString("UPDATE %1 SET `Part Number`=%2 where id=%2").arg(table_name).arg(id));
    }
    return query_status;
}

void CDatabaseCtrl::__AddBackticks(QStringList &str_list) {
    for (int i = 0; i < str_list.count(); ++i) {
        str_list[i] = "`" + str_list[i] + "`";
    }
}

void CDatabaseCtrl::__AddApostrophe(QStringList &str_list) {
    for (int i = 0; i <str_list.count(); ++i){
        str_list[i] = "\'"+str_list[i]+"\'";
    }
}
