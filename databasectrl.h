#ifndef DATABASECTRL_H
#define DATABASECTRL_H
#include <QSqlDatabase>

class databaseCtrl
{
public:
    databaseCtrl();
    QStringList getAllTablesNames() const;
    QSqlDatabase db;
private:
    bool connectDB();
};

#endif // DATABASECTRL_H
