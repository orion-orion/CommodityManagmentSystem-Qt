#include "mainwindow.h"
#include "dbconnect.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbConnect conDialog;
    if(conDialog.exec() != QDialog::Accepted)
        return -1;
    Login login;
    if(login.exec() != QDialog::Accepted)
        return -1;

    MainWindow w("commodity");
    //设置背景浅灰色
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::lightGray);
    w.setPalette(palette);
    w.setAutoFillBackground(true);
    w.show();

    return a.exec();
}
