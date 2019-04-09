#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QTextCodec>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(this->ui->txtname->text().trimmed()== tr("admin") && this->ui->txtpwd->text().trimmed()==tr("admin"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("Erorr"),tr("Username or password is wrong"),QMessageBox::Yes);
        this->ui->txtname->clear();
        this->ui->txtpwd->clear();
        this->ui->txtname->setFocus();
    }
}

void Login::on_pushButton_2_clicked()
{
    this->close();
}
