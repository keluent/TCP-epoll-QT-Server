#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
