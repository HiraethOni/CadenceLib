#ifndef DATABASECTRL_H
#define DATABASECTRL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

class databaseCtrl : public QObject
{
    Q_OBJECT
public:
    explicit databaseCtrl(QObject *parent=nullptr);
    Q_INVOKABLE QStringList getAllTablesNames() const;
    Q_INVOKABLE QString getAllContent(const QString tables_name) const;
    static QSqlDatabase db;
private:
    bool connectDB();
    QSqlQuery *p_query;
    QStringList table_column_name;
};

#endif // DATABASECTRL_H
