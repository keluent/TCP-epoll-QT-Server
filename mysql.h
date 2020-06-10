#ifndef MYSQL_H
#define MYSQL_H
#include <QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QDateTime>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
const QDateTime current_date_time = QDateTime::currentDateTime();
const QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

bool connect(const QString &dbName);

class MysqlTask : public QObject
{
public:
    MysqlTask();
    ~MysqlTask();
    void SqlExec(int x, int y, long z);
};


#endif // MYSQL_H
