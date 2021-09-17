#ifndef DATABASECTRL_H
#define DATABASECTRL_H
#include <QSqlDatabase>
#include <QObject>

class databaseCtrl : public QObject
{
    Q_OBJECT
public:
    explicit databaseCtrl(QObject *parent=nullptr);
    Q_INVOKABLE QStringList getAllTablesNames() const;
    static QSqlDatabase db;
private:
    bool connectDB();
};

#endif // DATABASECTRL_H
