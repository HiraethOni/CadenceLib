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
#if(QT_VERSION_MAJOR >= 6)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
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
    XLOG_TRACE("Read {}={}", group.toStdString(), value.toStdString());
    return value;
}

QStringList CConfigDatabase::ReadDatabase() {
    QStringList res;
    for(int i = 0; i < __db_conf_key_list.count(); i++){
        QString read_tmp = ReadInit(__db_conf_group, __db_conf_key_list[i]);
        res << read_tmp;
    }
    return res;
}

void CConfigDatabase::WriteDatabase(QStringList &str_list) {
    for(int i = 0; i < __db_conf_key_list.count(); i++){
        WriteInit(__db_conf_group, __db_conf_key_list[i], str_list[i]);
    }
}
