#ifndef CONFIGCTRL_H
#define CONFIGCTRL_H
#include <QString>
#include <QStringList>


class CConfigCtrl
{
public:
    CConfigCtrl();

    /**
     * 配置文件写入函数
     * @param group 组名
     * @param key key
     * @param value 值
     * @return 写入状态
     */
    bool WriteInit(QString group, QString key, QString value);
    /**
     * 配置文件读取函数
     * @param group 组名
     * @param key key
     * @param value 读取到的值的存放指针
     * @return 读取状态
     */
    bool ReadInit(QString group, QString key, QString &value);
    /**
     * 配置文件读取函数-直接返回读取结果
     * @param group 组名
     * @param key key
     * @return 读取值
     */
    QString ReadInit(QString group, QString key);

private:
    QString __initFilePath = "./config.ini";      // 配置文件所处路径
    /**
     * 检查程序运行目录内是否有配置文件
     * 没有则新建
     * @return
     */
    bool __CreateConfigFile();

    // 默认配置文件,注意路径需要加\转义
    QString __defaultConcig = R"([mariadb]
host=localhost
username=username
passwd=passwd
port=3306
database_name=databaseName
[language]
language=zh_CN
[Allegro Footprints]
path=X:\\ProgramData\\Cadence\\Cadence_Lib\\Library\\Package)";
};

/**
 * 专门读取数据库配置文件的派生类
 */
class CConfigDatabase : private CConfigCtrl
{
public:
    /**
     * 读取数据库配置文件
     * @return QStringList
     */
    QStringList ReadDatabase();
    /**
     * 写入数据库配置文件
     * @param str_list 待写入的列表
     */
    void WriteDatabase(QStringList &str_list);
private:
    QStringList __db_conf_key_list = {"host", "username", "passwd", "port", "database_name"};
    QString __db_conf_group = "mariadb";
};

#endif // CONFIGCTRL_H
