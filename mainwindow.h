#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QListWidget>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);
    MainWindow(const QString &commodityTable, QWidget *parent = 0);
    ~MainWindow();

private slots://槽函数
    void changeComView(QModelIndex index);//定位选择的行，并在右边list中显示出来
    void removeComFromComModel();//删除记录
    void searchSlot();//按name查找
    void search1Slot();//按category查找
    void returnSlot();//返回列表
    void addNewSlot();//添加按钮，创建添加记录的对话框
    void addNewToTable();//添加新记录到数据库
    void cancelBtnSlot();//添加对话框中的取消按钮
    void clearSlot();//清空行编辑(LineEdit)内容
    void quitBtnSlot();//退出程序

private:
    QGroupBox *createComGroup();
    QGroupBox *createDetailGroup();
    QSqlTableModel *comModel;
    QTableView *comView;
    QListWidget *showList;
    QListWidgetItem *item;

    QLineEdit *seLineEdit;
    QLineEdit *se1LineEdit;
    QLineEdit *idLineEdit;
    QLineEdit *categoryLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *originLineEdit;
    QLineEdit *countLineEdit;
    QLineEdit *priceLineEdit;
    QLineEdit *qualityLineEdit;
    QLineEdit *expLineEdit;
};

#endif // MAINWINDOW_H
