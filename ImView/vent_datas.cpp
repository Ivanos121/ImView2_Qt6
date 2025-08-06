#include "vent_datas.h"
#include "ui_vent_datas.h"
#include "doubledelegate.h"

#include <QFileInfo>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QStandardItemModel>

Vent_datas::Vent_datas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_datas)
{
    ui->setupUi(this);
    sdc = QSqlDatabase::addDatabase("QSQLITE");
    sdc.setDatabaseName(QFileInfo("../data/base_db/ventdb.db").absoluteFilePath());

    table();
}

Vent_datas::~Vent_datas()
{
    delete ui;
}

void Vent_datas::table()
{
    model = new QSqlTableModel;
    model->setTable("ventilators");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    QSortFilterProxyModel *proxy1 = new QSortFilterProxyModel();
    proxy1->setSourceModel(model);

    modd=new QStandardItemModel();
    modd->setSortRole(Qt::UserRole);

    for (int z =0; z< proxy1->rowCount(); ++z)
    {
        for (int y =0; y< proxy1->columnCount(); ++y)
        {
            QStandardItem *item = new QStandardItem();
            item->setData(proxy1->index(z,y).data().toString(), Qt::DisplayRole);
            item->setData(proxy1->index(z,y).data().toString(), Qt::UserRole);
            item->setTextAlignment(Qt::AlignCenter);
            modd->setItem(z,y,item);
        }
    }

    ui->tableView->setModel(modd);
    ui->tableView->setColumnHidden(0, true); //скрытие колонки id
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //выделение строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //выделение одной строки

    modd->setHeaderData(1, Qt::Horizontal, tr("Маркировка вентилятора"), Qt::DisplayRole);
    modd->setHeaderData(2, Qt::Horizontal, tr("Внутренний расчетный диаметр вентилятора, м"), Qt::DisplayRole);
    modd->setHeaderData(3, Qt::Horizontal, tr("Внешний расчетный диаметр вентилятора, м"), Qt::DisplayRole);
    modd->setHeaderData(4, Qt::Horizontal, tr("Ширина лопатки вентилятора, м"), Qt::DisplayRole);
    modd->setHeaderData(5, Qt::Horizontal, tr("Частота вращения вентилятора, об/мин"), Qt::DisplayRole);
    modd->setHeaderData(6, Qt::Horizontal, tr("Плотность воздуха, кг/м³"), Qt::DisplayRole);
    modd->setHeaderData(7, Qt::Horizontal, tr("Суммарная площадь отверстий в сетке кожуха, м²"), Qt::DisplayRole);
    modd->setHeaderData(8, Qt::Horizontal, tr("Общая площадь сетки кожуха, м²"), Qt::DisplayRole);
    modd->setHeaderData(9, Qt::Horizontal, tr("Площадь сечения в месте поворота к рабочему колесу, м²"), Qt::DisplayRole);
    modd->setHeaderData(10, Qt::Horizontal, tr("Угол поворота потока к входным кромкам лопаток рабочего колеса, град"), Qt::DisplayRole);
    modd->setHeaderData(11, Qt::Horizontal, tr("Площадь сечения в месте поворота перед входом в межреберные каналы, м²"), Qt::DisplayRole);
    modd->setHeaderData(12, Qt::Horizontal, tr("Угол поворота потока перед входом в межреберные каналы, град"), Qt::DisplayRole);
    modd->setHeaderData(13, Qt::Horizontal, tr("Площадь сечения перед входом в межреберные каналы, м²"), Qt::DisplayRole);
    modd->setHeaderData(14, Qt::Horizontal, tr("Площадь сечения межреберных каналов от станины до кожуха вентилятора, м²"), Qt::DisplayRole);
    modd->setHeaderData(15, Qt::Horizontal, tr("Угол натекания потока на ребра станины, град"), Qt::DisplayRole);
    modd->setHeaderData(16, Qt::Horizontal, tr("Угол поворота потока в межреберных каналах, град"), Qt::DisplayRole);

    QHeaderView *header=ui->tableView->horizontalHeader();
    //header->setSectionResizeMode(QHeaderView::ResizeToContents);

    int columnCount = modd->columnCount();

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

    modd->sort(2, Qt::DescendingOrder);
}
