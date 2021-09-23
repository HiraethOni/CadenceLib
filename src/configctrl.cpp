#include "configctrl.h"
#include "XLogger.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include <QSettings>

CConfigCtrl::CConfigCtrl()
{
    QFileInfo fileInfo(this->__initFilePath);
    if(!fileInfo.isFile()) {
        qDebug()<<"Config file not exist!";
        this->__CreateConfigFile();
    }
    XLOG_TRACE("Class CConfigCtrl Init");
}

bool CConfigCtrl::WriteInit(QString group, QString key, QString value)
{
    if(group.isEmpty() || key.isEmpty()) return false;
    QSettings config(this->__initFilePath, QSettings::IniFormat);
    config.beginGroup(group);
    config.setValue(key, value);
    config.endGroup();

    return true;
}

bool CConfigCtrl::ReadInit(QString group, QString key, QString &value)
{
    value.clear();
    if(group.isEmpty()||key.isEmpty()) return false;
    QSettings config(this->__initFilePath, QSettings::IniFormat);
    value = config.value(group+"/"+key).toString();

    return true;
}

bool CConfigCtrl::__CreateConfigFile()
{
    QFile file;
    file.setFileName(this->__initFilePath);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);
        out<<this->__defaultConcig;
    }
    file.close();
    return true;
}

QString CConfigCtrl::ReadInit(QString group, QString key) {
    QString value = "";
    if(group.isEmpty()||key.isEmpty()) return value;
    QSettings config(this->__initFilePath, QSettings::IniFormat);
    value = config.value(group+"/"+key).toString();
    XLOG_TRACE("Read Allegro Path {}", value.toStdString());
    return value;
}

QStringList CConfigDatabase::ReadDatabase() {
    QStringList res;
    for(int i = 0; i < __db_conf_key_list.count(); i++){
        QString read_tmp = ReadInit(__db_conf_group, __db_conf_key_list[i]);
        res << read_tmp;
        XLOG_DEBUG("{}={}",__db_conf_key_list[i].toStdString(), read_tmp.toStdString());
    }
    return res;
}

void CConfigDatabase::WriteDatabase(QStringList &str_list) {
    for(int i = 0; i < __db_conf_key_list.count(); i++){
        WriteInit(__db_conf_group, __db_conf_key_list[i], str_list[i]);
    }
}