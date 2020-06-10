#include "mysql.h"
#include <QMessageBox>




MysqlTask::MysqlTask()
{

}

MysqlTask::~MysqlTask()
{

}
/*
bool connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //    db.setHostName("host");
    //    db.setDatabaseName("dbname");
    //    db.setUserName("username");
    //    db.setPassword("password");
        db.setDatabaseName(dbName);
        if (!db.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  db.lastError().text());
            return false;
        }
        return true;
}
*/
void MysqlTask::SqlExec(int x,int y,long z)
{

   // mutex.lock();
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase db;
 /*   if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
*/
      db = QSqlDatabase::addDatabase("QSQLITE", QString("con%1").arg(z));
    db.setDatabaseName("test.db");
    db.open();
   // mutex.unlock();

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("tem");
    int row = model->rowCount();
    model->insertRows(model->rowCount(), 1);
    model->setData(model->index(row, 0), current_date);
    model->setData(model->index(row, 1), x);
    model->setData(model->index(row, 2), y);
    model->submitAll();
    delete model;
    printf("data is submitting\n");
    db.close();
    QString name;
        {
            name = QSqlDatabase::database().connectionName();
        }
    QSqlDatabase::removeDatabase(name);



}
