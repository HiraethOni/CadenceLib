#ifndef CONFIGCTRL_H
#define CONFIGCTRL_H
#include <QString>


class configCtrl
{
public:
    configCtrl();

    bool writeInit(QString group, QString key, QString value);
    bool readInit(QString group, QString key, QString &value);
    QString readInit(QString group, QString key);

private:
    QString initFilePath = "./config.ini";
    bool createConfigFile();

    QString defaultConcig = R"([mariadb]
host=localhost
username=username
passwd=passwd
datasheet=datasheet
[language]
language=zh_CN
[Allegro Footprints]
path=X:\\ProgramData\\Cadence\\Cadence_Lib\\Library\\Package)";
};

class configDatabase : private configCtrl
{
public:
    QStringList readDatabase();
};

#endif // CONFIGCTRL_H
