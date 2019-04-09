#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DbConnect;
}

class DbConnect: public QDialog//继承自QDialog类
{
    Q_OBJECT
public:
    explicit DbConnect(QWidget *parent = 0);//构造函数
    ~DbConnect();

    void createDB();//建立数据库

private slots:
    void on_submit_clicked();//连接槽函数
    void on_cancel_clicked();//取消槽函数

private:
    Ui::DbConnect *ui;
};

#endif // DBCONNECT_H
