#ifndef CONFIGCTRL_H
#define CONFIGCTRL_H
#include <QString>
#include <QStringList>


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
    void writeDatabase(QStringList &str_list);
private:
    QStringList db_conf_key_list = {"host", "username", "passwd", "datasheet"};
    QString db_conf_group = "mariadb";
};

#endif // CONFIGCTRL_H
