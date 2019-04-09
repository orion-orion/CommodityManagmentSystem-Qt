#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QPushButton>
#include <QSqlRecord>
#include <QMessageBox>
#include <QLabel>
#include <QtDebug>
#include <QSqlField>

MainWindow::MainWindow(const QString &commodityTable, QWidget *parent):
    QMainWindow(parent)
{
    //商品数据表模型
    comModel = new QSqlTableModel(this);
    comModel->setTable(commodityTable);
    comModel->select();

    QGroupBox *commodity = createComGroup();
    QGroupBox *detail = createDetailGroup();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(commodity, 0, 0, 2, 1);
    layout->addWidget(detail, 0, 1, 2, 1);
    layout->setColumnMinimumWidth(0, 500);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    resize(850, 400);
}

QGroupBox* MainWindow::createComGroup()//左边组合框
{
    comView = new QTableView;
    comView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑状态
    comView->setSortingEnabled(true);//开启排序
    comView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择，选一行
    comView->setSelectionMode(QAbstractItemView::SingleSelection);//单击选择
    comView->setShowGrid(true);
    comView->setAlternatingRowColors(true);
    comView->setModel(comModel);
    connect(comView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeComView(QModelIndex)));

    QGroupBox *box = new QGroupBox(tr("Info"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(comView, 0, 0);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createDetailGroup()//右边细节组合框
{
    QGroupBox *box = new QGroupBox(tr("Detail"));
    showList = new QListWidget;

    QPushButton *deleteBtn = new QPushButton(tr("delete"));
    QPushButton *addBtn = new QPushButton(tr("add"));
    QPushButton *searchBtn = new QPushButton(tr("search by name"));
    QPushButton *search1Btn = new QPushButton(tr("search by category"));
    QPushButton *returnBtn = new QPushButton(tr("return"));
    QPushButton *quitBtn = new QPushButton(tr("quit"));

    connect(deleteBtn, SIGNAL(clicked(bool)), this, SLOT(removeComFromComModel()));
    connect(addBtn, SIGNAL(clicked(bool)), this, SLOT(addNewSlot()));
    connect(searchBtn, SIGNAL(clicked(bool)), this, SLOT(searchSlot()));
    connect(search1Btn, SIGNAL(clicked(bool)), this, SLOT(search1Slot()));
    connect(returnBtn, SIGNAL(clicked(bool)), this, SLOT(returnSlot()));
    connect(quitBtn, SIGNAL(clicked(bool)), this, SLOT(quitBtnSlot()));

    seLineEdit = new QLineEdit;
    se1LineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(showList, 0, 0, 3, 2);
    layout->addWidget(deleteBtn, 3, 0, 1, 1);
    layout->addWidget(addBtn, 3, 1, 1, 1);
    layout->addWidget(seLineEdit, 4, 0, 1, 1);
    layout->addWidget(searchBtn, 4, 1, 1, 1);
    layout->addWidget(se1LineEdit, 5, 0, 1, 1);
    layout->addWidget(search1Btn, 5, 1, 1, 1);
    layout->addWidget(returnBtn, 6, 0, 1, 1);
    layout->addWidget(quitBtn, 6, 1, 1, 1);

    box->setLayout(layout);
    return box;
}
//当选中一行时，改变视图，右侧列表框显示详细信息
void MainWindow::changeComView(QModelIndex index)
{
    showList->clear();
    item = new QListWidgetItem(showList);
    //获取选中行数据表中的数据并分离出来
    QSqlRecord record = comModel->record(index.row());
    int comId = record.value("id").toInt();
    QString category = record.value("category").toString();
    QString name = record.value("name").toString();
    QString origin = record.value("origin").toString();
    int count = record.value("count").toInt();
    double price = record.value("price").toDouble();
    QString quality = record.value("quality").toString();
    QString exp = record.value("exp").toString();
    item->setText(tr("ID: %1\nCategory: %2\nName: %3\nOrigin: %4\nCount: %5\nPrice: %6\nQuality: %7\nExp: %8\n").arg(comId).arg(category).arg(name).arg(origin).arg(count).arg(price).arg(quality).arg(exp));
}

void MainWindow::removeComFromComModel()
{
    QModelIndexList select = comView->selectionModel()->selectedRows();

    if(!select.empty())
    {
        QModelIndex idIndex = select.at(0);//得到选中行的id索引
        QString name = idIndex.sibling(idIndex.row(), 2).data().toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Delete"), QString(tr("Are you sure to delete '%1' information?").arg(name)), QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            comModel->removeRow(idIndex.row());
            comModel->submitAll();
            comModel->select();
        }
    }
}
//按name查找
void MainWindow::searchSlot()
{
    QString name = seLineEdit->text();
    if(!name.isEmpty())
    {
        comModel->setFilter(QObject::tr("name = '%1'").arg(name));
        comModel->select();
        seLineEdit->clear();
    }
    else
        return;
}
//按category查找
void MainWindow::search1Slot()
{
    QString category = se1LineEdit->text();
    if(!category.isEmpty())
    {
        comModel->setFilter(QObject::tr("category = '%1'").arg(category));
        comModel->select();
        se1LineEdit->clear();
    }
    else
        return;
}

void MainWindow::returnSlot()
{
    comModel->setTable("commodity");
    comModel->setSort(0, Qt::AscendingOrder);
    comModel->select();
}

void MainWindow::addNewSlot()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(tr("Add"));

    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton(tr("Submit"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(addNewToTable()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));

    QLabel *idLabel = new QLabel(tr("ID: "));
    QLabel *categoryLabel = new QLabel(tr("Category: "));
    QLabel *nameLabel = new QLabel(tr("Name: "));
    QLabel *originLabel = new QLabel(tr("Origin: "));
    QLabel *countLabel = new QLabel(tr("Count: "));
    QLabel *priceLabel = new QLabel(tr("Price: "));
    QLabel *qualityLabel = new QLabel(tr("Quality"));
    QLabel *expLabel = new QLabel(tr("Exp"));

    idLineEdit = new QLineEdit;
    categoryLineEdit = new QLineEdit;
    nameLineEdit = new QLineEdit;
    originLineEdit = new QLineEdit;
    countLineEdit = new QLineEdit;
    priceLineEdit = new QLineEdit;
    qualityLineEdit = new QLineEdit;
    expLineEdit = new QLineEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(idLabel, 0, 0, 1, 1);
    layout->addWidget(idLineEdit, 0, 1, 1, 1);
    layout->addWidget(categoryLabel, 1, 0, 1, 1);
    layout->addWidget(categoryLineEdit, 1, 1, 1, 1);
    layout->addWidget(nameLabel, 2, 0, 1, 1);
    layout->addWidget(nameLineEdit, 2, 1, 1, 1);
    layout->addWidget(originLabel, 3, 0, 1, 1);
    layout->addWidget(originLineEdit, 3, 1, 1, 1);
    layout->addWidget(countLabel, 4, 0, 1, 1);
    layout->addWidget(countLineEdit, 4, 1, 1, 1);
    layout->addWidget(priceLabel, 5, 0, 1, 1);
    layout->addWidget(priceLineEdit, 5, 1, 1, 1);
    layout->addWidget(qualityLabel, 6, 0, 1, 1);
    layout->addWidget(qualityLineEdit, 6, 1, 1, 1);
    layout->addWidget(expLabel, 7, 0, 1, 1);
    layout->addWidget(expLineEdit, 7, 1, 1, 1);
    layout->addWidget(submitBtn, 8, 0, 1, 1);
    layout->addWidget(cancelBtn, 8, 1, 1, 1);

    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    dialog->setLayout(mainLayout);
    dialog->show();
}
//将新数据添加到数据库中
void MainWindow::addNewToTable()
{
    int id = idLineEdit->text().toInt();
    QString category = categoryLineEdit->text();
    QString name = nameLineEdit->text();
    QString origin = originLineEdit->text();
    int count = countLineEdit->text().toInt();
    double price = priceLineEdit->text().toDouble();
    QString quality = qualityLineEdit->text();
    QString exp = expLineEdit->text();

    qDebug() << id << category << name << origin << count << price << quality << exp;
    QSqlRecord record;
    QSqlField f1("id", QVariant::Int);
    QSqlField f2("category", QVariant::String);
    QSqlField f3("name", QVariant::String);
    QSqlField f4("origin", QVariant::String);
    QSqlField f5("count", QVariant::Int);
    QSqlField f6("price", QVariant::Double);
    QSqlField f7("quality", QVariant::String);
    QSqlField f8("exp", QVariant::String);

    f1.setValue(QVariant(id));
    f2.setValue(QVariant(category));
    f3.setValue(QVariant(name));
    f4.setValue(QVariant(origin));
    f5.setValue(QVariant(count));
    f6.setValue(QVariant(price));
    f7.setValue(QVariant(quality));
    f8.setValue(QVariant(exp));

    record.append(f1);
    record.append(f2);
    record.append(f3);
    record.append(f4);
    record.append(f5);
    record.append(f6);
    record.append(f7);
    record.append(f8);

    comModel->insertRecord(-1, record);
    comModel->setSort(0, Qt::AscendingOrder);//设置升序排列
    comModel->select();
    clearSlot();
}

void MainWindow::cancelBtnSlot()
{
    clearSlot();
}

void MainWindow::clearSlot()
{
    idLineEdit->clear();
    categoryLineEdit->clear();
    nameLineEdit->clear();
    originLineEdit->clear();
    countLineEdit->clear();
    priceLineEdit->clear();
    qualityLineEdit->clear();
    expLineEdit->clear();
}

void MainWindow::quitBtnSlot()
{
    this->close();
}

MainWindow::~MainWindow()
{
    //delete ui;
}
