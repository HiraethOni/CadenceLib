#include "configctrl.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSettings>

configCtrl::configCtrl()
{
    qDebug()<<"Class configCtrl Init";
    this->createConfigFile();
}

bool configCtrl::writeInit(QString group, QString key, QString value)
{
    if(group.isEmpty() || key.isEmpty()) return false;
    QSettings config(this->initFilePath, QSettings::IniFormat);
    config.beginGroup(group);
    config.setValue(key, value);
    config.endGroup();

    return true;
}

bool configCtrl::readInit(QString group, QString key, QString &value)
{
    value.clear();
    if(group.isEmpty()||key.isEmpty()) return false;
    QSettings config(this->initFilePath, QSettings::IniFormat);
    value = config.value(group+"/"+key).toString();

    return true;
}

bool configCtrl::createConfigFile()
{
    QFile file;
    file.setFileName(this->initFilePath);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<this->defaultConcig;
    }
    file.close();
    return true;
}

QString configCtrl::readInit(QString group, QString key) {
    QString value = "";
    if(group.isEmpty()||key.isEmpty()) return value;
    QSettings config(this->initFilePath, QSettings::IniFormat);
    value = config.value(group+"/"+key).toString();
    qDebug()<<group<<key<<value;
    return value;
}

QStringList configDatabase::readDatabase() {
    QStringList res;
    for(int i = 0; i < db_conf_key_list.count(); i++){
        res << readInit(db_conf_group, db_conf_key_list[i]);
    }
    return res;
}

void configDatabase::writeDatabase(QStringList &str_list) {
    for(int i = 0; i < db_conf_key_list.count(); i++){
        writeInit(db_conf_group, db_conf_key_list[i], str_list[i]);
    }
}
