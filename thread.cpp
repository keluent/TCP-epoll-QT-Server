#include "thread.h"
#include "mainwindow.h"
#include "mysql.h"
#include <QThread>

SqlTask::SqlTask()
{

}

SqlTask::~SqlTask()
{

}

void SqlTask::run()
{
    MysqlTask mysqltask;
    mysqltask.SqlExec(x, y, z);
}


