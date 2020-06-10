#ifndef THREAD_H
#define THREAD_H

#include <QRunnable>
#include <QThreadPool>
#include <QObject>
#include <QThread>
class SqlTask :  public QRunnable
{
   // Q_OBJECT

public:
    int y;
    int x;
    int z;
    SqlTask();
    ~SqlTask();
    void run();


};




#endif // THREAD_H
