#include "datas.h"
#include "qsqlquery.h"
#include "ui_datas.h"
#include "base.h"
#include "MySortFilterProxyModel.h"
#include "doubledelegate.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QTableView>
#include <QStyle>
//#include <QDesktopWidget>
#include <QPainter>
#include <QIntValidator>
#include <QFileDialog>
#include <QScreen>

datas::datas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::datas)
{
    ui->setupUi(this);

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(QFileInfo("../data/base_db/mydb.db").absoluteFilePath());

    table();

    ui->widget_2->setVisible(false);
   // QHeaderView *tableHeader = ui->tableView->horizontalHeader();
    //connect(tableHeader, &QHeaderView::sectionClicked, this, &datas::on_sectionClicked);
}

datas::~datas()
{
    delete ui;
}

void datas::table()
{
    model = new QSqlTableModel;
    model->setTable("dvigatels");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    QSortFilterProxyModel *proxy1 = new QSortFilterProxyModel();
    proxy1->setSourceModel(model);
    // proxy1->setAlignment(0, Qt::AlignCenter);
    // proxy1->setAlignment(1, Qt::AlignCenter);

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

    modd->setHeaderData(1, Qt::Horizontal, tr("Марка двигателя"), Qt::DisplayRole);
    modd->setHeaderData(2, Qt::Horizontal, tr("Номинальная мощность двигателя, Вт"), Qt::DisplayRole);
    modd->setHeaderData(3, Qt::Horizontal, tr("Номинальная частота вращения, об/мин"), Qt::DisplayRole);
    modd->setHeaderData(4, Qt::Horizontal, tr("Номинальное напряжение фазы, В"), Qt::DisplayRole);
    modd->setHeaderData(5, Qt::Horizontal, tr("Номинальный коэффициент мощности"), Qt::DisplayRole);
    modd->setHeaderData(6, Qt::Horizontal, tr("Номинальный коэффициент полезного действия"), Qt::DisplayRole);
    modd->setHeaderData(7, Qt::Horizontal, tr("Кратность максимального момента"), Qt::DisplayRole);
    modd->setHeaderData(8, Qt::Horizontal, tr("Синхронная частота вращения, об/мин"), Qt::DisplayRole);
    modd->setHeaderData(9, Qt::Horizontal, tr("Момент инерции, кг·м²"), Qt::DisplayRole);
    modd->setHeaderData(10, Qt::Horizontal, tr("Класс изоляции"), Qt::DisplayRole);

    QHeaderView *header=ui->tableView->horizontalHeader();

    for(int i=1;i<10;i++)
    {
      header->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }

    for(int i=1;i<10;i++)
    {
        ui->tableView->horizontalHeader()->setSectionsClickable(i);

    }

    ui->tableView->resizeRowsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setFixedHeight(100);
    ui->tableView->setItemDelegate(new DoubleDelegate(ui->tableView));

    ui->tableView->setSortingEnabled(true);

    modd->sort(2, Qt::DescendingOrder);
}

void datas::zapis()
{
    QSqlQuery query=QSqlQuery(sdb);
    query.prepare("INSERT INTO dvigatels (id, name, pn, n, un, cosf, kpd, mk, n0, ki) "
                  "VALUES (:id, :name, :pn, :n, :un, :cosf, :kpd, :mk, :n0, :ki)");
    query.bindValue(":id", QVariant(QVariant::String));
    query.bindValue(":name", QString(base.name));
    query.bindValue(":pn",QString::number(base.P_nom, 'f', 3));
    query.bindValue(":n",QString("%1").arg(base.n_nom, 0, 'f', 3));
    query.bindValue(":un",QString("%1").arg(base.U_fnom, 0, 'f', 3));
    query.bindValue(":cosf",QString("%1").arg(base.cosf_nom, 0, 'f', 3));
    query.bindValue(":kpd",QString("%1").arg(base.kpd_nom, 0, 'f', 3));
    query.bindValue(":mk",QString("%1").arg(base.muk, 0, 'f', 3));
    query.bindValue(":n0",QString("%1").arg(base.n_0, 0, 'f', 3));
    query.bindValue(":j",QString("%1").arg(base.J_dv, 0, 'f', 3));
    query.bindValue(":ki",QString("%1").arg(base.ki));
    if(!query.exec()){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }
}

void datas::zapis_from_cell_tableview()
{
    QModelIndex myIndexs;
    int id = ui->tableView->currentIndex().row();
    int column = ui->tableView->currentIndex().column();
    myIndexs = ui->tableView->model()->index(id, column, QModelIndex());
    QString strs = ui->tableView->model()->data(myIndexs).toString();

    int ids = ui->tableView->model()->data(ui->tableView->model()->index(id, 0, QModelIndex())).toInt();

    QSqlQuery query = QSqlQuery(sdb);

    if(column == 1)
    {
        query.prepare("UPDATE dvigatels SET name=:name WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":name", strs);
    }

    if(column == 2)
    {
        query.prepare("UPDATE dvigatels SET pn=:pn WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":pn", strs);
    }

    if(column == 3)
    {
        query.prepare("UPDATE dvigatels SET n=:n WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":n", strs);
    }

    if(column == 4)
    {
        query.prepare("UPDATE dvigatels SET un=:un WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":un", strs);
    }

    if(column == 5)
    {
        query.prepare("UPDATE dvigatels SET cosf=:cosf WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":cosf", strs);
    }

    if(column == 6)
    {
        query.prepare("UPDATE dvigatels SET kpd=:kpd WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":kpd", strs);
    }

    if(column == 7)
    {
        query.prepare("UPDATE dvigatels SET mk=:mk WHERE id=:id");
        query.bindValue(":id", ids);
        query.bindValue(":mk", strs);
    }

    if(column == 8)
    {
        query.prepare("UPDATE dvigatels SET n0=:n0 WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":no", strs);
    }

    if(column == 9)
    {
        query.prepare("UPDATE dvigatels SET j=:j WHERE id=:id");
        query.bindValue(":id", ui->tableView->currentIndex().row());
        query.bindValue(":j", strs);
    }
    if(column == 10)
    {
        query.prepare("UPDATE dvigatels SET ki=:ki WHERE id=:id");
        query.bindValue(":id", ids);
        query.bindValue(":ki", strs);
    }

    if(!query.exec())
    {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }
}

void datas::deleteDannieS()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if(selectModel->selectedRows().isEmpty())
    {
        QMessageBox::critical(this, tr("Ошибка!"), tr("Выберите необходимую строку"));
    }
    else
    {
    QSqlQuery query=QSqlQuery(sdb);
    int rowNumber = ui->tableView->selectionModel()->selection().indexes()[0].row();
    query.prepare("DELETE FROM dvigatels WHERE id=:id");
    query.bindValue(":id", ui->tableView->model()->index(rowNumber, 0).data().toString());
    query.exec();
    table();
    }
}

void datas::saveDannieS()
{
    model->database().transaction();
        if(model->submitAll())
            model->database().commit();
        else
            model->database().rollback();
}

void datas::enterDannieS()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    isdn=new ischodn_dannie(this);
    isdn->wf = this;
    isdn->exec();
    isdn->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    isdn->size(),
    screen->geometry()));
}

void datas::onsectionClicked(int index)
{
    modd->sort(index,Qt::AscendingOrder);
}





