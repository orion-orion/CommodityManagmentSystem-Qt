#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
    class Login;
}

class Login : public QDialog {
    Q_OBJECT
public:
    Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;

private slots:
    void on_pushButton_2_clicked();//登录槽函数
    void on_pushButton_clicked();//取消槽函数
};

#endif // LOGIN_H
