#include "configctrl.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSettings>

configCtrl::configCtrl()
{
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
