#include "dbconnect.h"
#include "ui_dbconnect.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QtDebug>
#include <QSqlQuery>

DbConnect::DbConnect(QWidget *parent):
    QDialog(parent),
    ui(new Ui::DbConnect)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();//返回所有可用的数据库驱动的清单
    ui->dbComboBox->addItems(drivers);
    ui->status_Label->setText(tr("状态:"));
}

DbConnect::~DbConnect()
{
    delete ui;
}

void DbConnect::on_submit_clicked()//连接槽函数
{
    if(ui->dbComboBox->currentText().isEmpty())
    {
        ui->status_Label->setText(tr("Please choose a sql driver"));
        ui->dbComboBox->setFocus();
    }
    else if(ui->dbComboBox->currentText() == "QSQLITE")//使用sqlite数据库
    {
        createDB();
        accept();
    }
    else
    {
        QMessageBox::information(this, tr("SQL"), tr("Sorry, only QSQLITE avaliable!"));
    }
}
//创建数据库文件commodity.db
void DbConnect::createDB()
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(("QSQLITE"));
    db.setDatabaseName("commodity.db");
    db.open();
    if(!db.open())
    {
        err = db.lastError();
        qDebug() << err.text();
    }
    else
    {
        ui->status_Label->setText(tr("Create sqlite successfully!"));
    }

    QSqlQuery q;//数据库操作,执行数据库语句
    bool success = q.exec("create table commodity(id int primary key, category varchar(40), name varchar(40), origin varchar(40), count int, price double, quality varchar(40), exp varchar(40))");
    if(success)
    {
        qDebug() << QObject::tr("Create commodity table successfully!");
    }
}

void DbConnect::on_cancel_clicked()
{
    close();
}
