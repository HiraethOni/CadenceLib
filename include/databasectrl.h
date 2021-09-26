#ifndef DATABASECTRL_H
#define DATABASECTRL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

/**
 * 数据库查询组件,供QML调用
 */
class CDatabaseCtrl : public QObject
{
    /**
     * 若想将类借口暴露给QML调用,则类必须继承自Q_OBJET并且启用宏说明
     * 这里注意一点:如果工程编译完之后再引入Q_OBJECT的话,工程重新生成一次
     * 直接编译会报错,貌似和moc实现有关系
     */
    Q_OBJECT
public:
    /**
     * 构造函数,里面初始化了数据库表格字段与数据库指针
     * @param parent
     */
    explicit CDatabaseCtrl(QObject *parent=nullptr);

    /**
     * 获取所有表的名字
     * @return 数据库表名
     */
    Q_INVOKABLE QStringList getAllTablesNames() const;

    /**
     * 获取数据库字段值
     * @param tables_name
     * @return
     */
    Q_INVOKABLE QStringList getFiledValue(const QString field, const QString tables_name) const;

    /**
     * 获取数据库所有内容
     * @param tables_name 表名
     * @return 数据库内容(json格式)
     */
    Q_INVOKABLE QString getAllContent(const QString tables_name) const;

    /**
     * 扫描封装路径
     * @return
     */
    Q_INVOKABLE QStringList scanPackageDir() const;

    /**
     * 插入数据
     * @param data 待插入数据的列表,List
     * @return 插入状态
     */
    Q_INVOKABLE bool insertData(QString table_name, QStringList data) const;
//    Q_INVOKABLE void saveChanges(const QString json) const;

    /**
     * 数据库指针,这里声明为静态类型是为了方便继承的时候不用再初始化这个指针
     */
    static QSqlDatabase sm_db;
private:
    bool __ConnectDB();       // 连接数据库
    QSqlQuery *__m_p_query;     // 数据库查询指针
    QStringList __m_table_column_name;  // 数据库字段名

    /**
     * 给字符串列表里面的每一个值添加反引号
     * @param str_list 字符串列表
     */
    static inline void __AddBackticks(QStringList& str_list) ;
    /**
     * 给字符串列表的每一个值添加单引号
     * @param str_list
     */
    static inline void __AddApostrophe(QStringList& str_list) ;
};

#endif // DATABASECTRL_H
