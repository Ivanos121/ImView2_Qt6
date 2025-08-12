#include "vent_datas.h"
#include "qscreen.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_vent_datas.h"
#include "doubledelegate.h"
#include "vent_settings.h"
#include "Base_tepl_vent.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QStandardItemModel>

Vent_datas::Vent_datas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_datas)
{
    ui->setupUi(this);

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

void Vent_datas::zapis()
{
    QSqlQuery query(QSqlDatabase::database("connection2"));
    query.prepare("INSERT INTO ventilators (id, name, d1p, d2p, b, n, ro, sotv, s0, s1, a1, s2, a2, s3, s4 ,fi, fi2) "
                  "VALUES (:id, :name, :d1p, :d2p, :b, :n, :ro, :sotv, :s0, :s1, :a1, :s2, :a2, :s3, :s4, :fi, :fi2)");
    query.bindValue(":id", QVariant(QString()));
    query.bindValue(":name", QString(ventparam.name));
    query.bindValue(":d1p",QString::number(ventparam.d1p, 'f', 3));
    query.bindValue(":d2p",QString("%1").arg(ventparam.d2p, 0, 'f', 3));
    query.bindValue(":b",QString("%1").arg(ventparam.b, 0, 'f', 3));
    query.bindValue(":n",QString("%1").arg(ventparam.n, 0, 'f', 3));
    query.bindValue(":ro",QString("%1").arg(ventparam.ro, 0, 'f', 3));
    query.bindValue(":sotv",QString("%1").arg(ventparam.sotv, 0, 'f', 3));
    query.bindValue(":s0",QString("%1").arg(ventparam.s0, 0, 'f', 3));
    query.bindValue(":s1",QString("%1").arg(ventparam.s1, 0, 'f', 3));
    query.bindValue(":a1",QString("%1").arg(ventparam.a1, 0, 'f', 3));
    query.bindValue(":s2",QString("%1").arg(ventparam.s2, 0, 'f', 3));
    query.bindValue(":a2",QString("%1").arg(ventparam.a2, 0, 'f', 3));
    query.bindValue(":s3",QString("%1").arg(ventparam.s3, 0, 'f', 3));
    query.bindValue(":s4",QString("%1").arg(ventparam.s4, 0, 'f', 3));
    query.bindValue(":fi",QString("%1").arg(ventparam.fi, 0, 'f', 3));
    query.bindValue(":fi2",QString("%1").arg(ventparam.fi2, 0, 'f', 3));
    if(!query.exec()){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }
}

void Vent_datas::enterDannieV()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    vsn=new Vent_settings(this);
    vsn->wf = this;
    vsn->exec();
    vsn->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            vsn->size(),
            screen->geometry()));
}

void Vent_datas::saveDannieV()
{
    model2->database().transaction();
    if(model2->submitAll())
        model2->database().commit();
    else
        model2->database().rollback();
}


void Vent_datas::deleteDannieV()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if(selectModel->selectedRows().isEmpty())
    {
        QMessageBox::critical(this, tr("Ошибка!"), tr("Выберите необходимую строку"));
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database("connection2"));
        int rowNumber = ui->tableView->selectionModel()->selection().indexes()[0].row();
        query.prepare("DELETE FROM ventilators WHERE id=:id");
        query.bindValue(":id", ui->tableView->model()->index(rowNumber, 0).data().toString());
        query.exec();
        table();
    }
}
