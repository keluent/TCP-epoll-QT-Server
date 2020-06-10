#include "mainwindow.h"
#include "mysql.h"
#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
//#include <crypt.h>
#include <QApplication>
#include <unistd.h>
#include <arpa/inet.h>
#define MAXLINE 80
#define SERV_PORT 54321
#define OPEN_MAX 60000

int decrypt(int a)
{
  a = a / 4;
  a -= 2;
  return a;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //线程池
    QThreadPool *pool =   QThreadPool::globalInstance();



    pool->setMaxThreadCount(10);



    int listenfd, connfd, sockfd, n;
    int i, j;
    ssize_t nready, efd, res; //ssize_t有符号整型,在32位机上是int,在64位机上是long int
    int buff[MAXLINE],str[INET_ADDRSTRLEN];
    socklen_t clilen;
    int client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event tep, ep[OPEN_MAX];//tep注册事件,ep[]用来回传要处理的事件
    char goback[50] = "got! ";
      /*
        epoll_event的定义
        struct epoll_event
        {
        __uint32_t events;       //epoll事件
        epoll_data_t data;       //用户数据
        }

        epoll_data_t:

        typedef union epoll_data
        {
        void* ptr;
        int fd;         //用的最多,是指定事件从属的目标文件描述符
        uint32_t u32;
        uint64_t u64;
        }epoll_data_t
       */
 /*   if (connect("test.db"))
    {
        QSqlQuery query;
        if (!query.exec("CREATE TABLE tem ("
                                "time  TIME,"
                                "number ,"
                                "temperature)"))
        {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query.lastError().text());
        }
*/

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr *)  &servaddr, sizeof(servaddr));
    listen(listenfd, 20);

    efd = epoll_create(OPEN_MAX);
    tep.events = EPOLLIN;
    tep.data.fd = listenfd;
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);
    long s =0;
    for (;;)
      {
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); //表示有多少文件描述符就绪
        for( i=0;i<nready;i++)
        {

            s++;
          if(ep[i].data.fd == listenfd)
          {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

            printf("received from message at PORT %d\n", SERV_PORT);
            //printf("received %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), SERV_PORT);

            tep.events = EPOLLIN;
            tep.data.fd = connfd;
            res = epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);


          }
          else
          {
            sockfd = ep[i].data.fd;
            n = read(sockfd, buff, MAXLINE);
            if (n == 0)
            {
              res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
              close(sockfd);
              printf("client[%d] closed connection\n", j);
            }
            else
            {
              buff[1] = decrypt(buff[1]);
              printf("num:%d, temperature:%d\n", buff[0], buff[1]);
              //将数据存入数据库
              printf("%d\n",s);
              SqlTask *task = new  SqlTask();

              task->x = buff[0];
              task->y = buff[1];
              task->z = s;
              pool->globalInstance()->start(task);
              write(sockfd, goback, n);

            }

          }

        }
      }



    return a.exec();

}
