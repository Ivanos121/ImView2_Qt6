#include "vent_datas.h"
#include "ui_vent_datas.h"
#include "doubledelegate.h"

#include <QFileInfo>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QSqlDatabase>

Vent_datas::Vent_datas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_datas)
{
    ui->setupUi(this);
    // QSqlDatabase::removeDatabase("connection2");
    // sdc = QSqlDatabase::addDatabase("QSQLITE", "connection2");
    // sdc.setDatabaseName(QFileInfo("../data/base_db/ventdb.db").absoluteFilePath());
    // if (!sdc.open()) {
    //     qDebug() << "Ошибка открытия базы данных 2:" << sdc.lastError().text();
    //     return;
    // }
    // else
    // {
    //     qDebug() << "база загружена2";
    // }

    table();
}

Vent_datas::~Vent_datas()
{
    delete ui;
}

void Vent_datas::table()
{
    model2 = new QSqlTableModel(this, QSqlDatabase::database("connection2"));
    model2->setTable("ventilators");
    model2->setEditStrategy(QSqlTableModel::OnFieldChange);
    model2->select();

    QSortFilterProxyModel *proxy2 = new QSortFilterProxyModel();
    proxy2->setSourceModel(model2);

    modd2=new QStandardItemModel();
    modd2->setSortRole(Qt::UserRole);

    for (int z =0; z< proxy2->rowCount(); ++z)
    {
        for (int y =0; y< proxy2->columnCount(); ++y)
        {
            QStandardItem *item = new QStandardItem();
            item->setData(proxy2->index(z,y).data().toString(), Qt::DisplayRole);
            item->setData(proxy2->index(z,y).data().toString(), Qt::UserRole);
            item->setTextAlignment(Qt::AlignCenter);
            modd2->setItem(z,y,item);
        }
    }

    ui->tableView->setModel(modd2);
    ui->tableView->setColumnHidden(0, true); //скрытие колонки id
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //выделение строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //выделение одной строки

    modd2->setHeaderData(1, Qt::Horizontal, tr("Маркировка вентилятора"), Qt::DisplayRole);
    modd2->setHeaderData(2, Qt::Horizontal, tr("Внутренний расчетный диаметр вентилятора, м"), Qt::DisplayRole);
    modd2->setHeaderData(3, Qt::Horizontal, tr("Внешний расчетный диаметр вентилятора, м"), Qt::DisplayRole);
    modd2->setHeaderData(4, Qt::Horizontal, tr("Ширина лопатки вентилятора, м"), Qt::DisplayRole);
    modd2->setHeaderData(5, Qt::Horizontal, tr("Частота вращения вентилятора, об/мин"), Qt::DisplayRole);
    modd2->setHeaderData(6, Qt::Horizontal, tr("Плотность воздуха, кг/м³"), Qt::DisplayRole);
    modd2->setHeaderData(7, Qt::Horizontal, tr("Суммарная площадь отверстий в сетке кожуха, м²"), Qt::DisplayRole);
    modd2->setHeaderData(8, Qt::Horizontal, tr("Общая площадь сетки кожуха, м²"), Qt::DisplayRole);
    modd2->setHeaderData(9, Qt::Horizontal, tr("Площадь сечения в месте поворота к рабочему колесу, м²"), Qt::DisplayRole);
    modd2->setHeaderData(10, Qt::Horizontal, tr("Угол поворота потока к входным кромкам лопаток рабочего колеса, град"), Qt::DisplayRole);
    modd2->setHeaderData(11, Qt::Horizontal, tr("Площадь сечения в месте поворота перед входом в межреберные каналы, м²"), Qt::DisplayRole);
    modd2->setHeaderData(12, Qt::Horizontal, tr("Угол поворота потока перед входом в межреберные каналы, град"), Qt::DisplayRole);
    modd2->setHeaderData(13, Qt::Horizontal, tr("Площадь сечения перед входом в межреберные каналы, м²"), Qt::DisplayRole);
    modd2->setHeaderData(14, Qt::Horizontal, tr("Площадь сечения межреберных каналов от станины до кожуха вентилятора, м²"), Qt::DisplayRole);
    modd2->setHeaderData(15, Qt::Horizontal, tr("Угол натекания потока на ребра станины, град"), Qt::DisplayRole);
    modd2->setHeaderData(16, Qt::Horizontal, tr("Угол поворота потока в межреберных каналах, град"), Qt::DisplayRole);

    QHeaderView *header=ui->tableView->horizontalHeader();
    //header->setSectionResizeMode(QHeaderView::ResizeToContents);

    int columnCount = modd2->columnCount();

    for(int i=1;i<columnCount;i++)
    {
        header->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }

    ui->tableView->resizeColumnsToContents();

    for(int i=1;i<columnCount;i++)
    {
        ui->tableView->horizontalHeader()->setSectionsClickable(i);

    }

    ui->tableView->resizeRowsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setFixedHeight(150);
    ui->tableView->setItemDelegate(new DoubleDelegate(ui->tableView));

    ui->tableView->setSortingEnabled(true);

    modd2->sort(2, Qt::DescendingOrder);
}
