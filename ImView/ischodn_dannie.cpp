#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

#include "ischodn_dannie.h"
#include "ui_ischodn_dannie.h"
#include "base.h"
#include "datas.h"

ischodn_dannie::ischodn_dannie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ischodn_dannie)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Величина" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(true);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    //ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("марка двигателя:"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Номинальная мощность двигателя, кВт:"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Номинальная частота вращения, об/мин:"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Номинальное напряжение фазы, В"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Номинальный коэффициент мощности"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Номинальный коэффициент полезного действия"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Кратность максимального момента"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Синхронная частота вращения, об/мин"));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Момент инерции, кг*м2"));
    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Класс изоляции"));

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(8, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(9, 1, new QTableWidgetItem());

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_17=ui->tableWidget->palette();
    p_17.setColor(QPalette::Base, QColor(255, 255, 191));
    p_17.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p_17);

    connect(ui->pushButton, &QPushButton::clicked, this, &ischodn_dannie::apply_dannie);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ischodn_dannie::close_dialog);

}

ischodn_dannie::~ischodn_dannie()
{
    delete ui;
}

void ischodn_dannie::close_dialog()
{
    close();
}


void ischodn_dannie::apply_dannie()
{
    base.name = ui->tableWidget->item(0,1)->text();
    base.P_nom = ui->tableWidget->item(1,1)->text().toDouble();
    base.n_nom = ui->tableWidget->item(2,1)->text().toDouble();
    base.U_fnom = ui->tableWidget->item(3,1)->text().toDouble();
    base.cosf_nom = ui->tableWidget->item(4,1)->text().toDouble();
    base.kpd_nom = ui->tableWidget->item(5,1)->text().toDouble();
    base.muk = ui->tableWidget->item(6,1)->text().toDouble();
    base.n_0 = ui->tableWidget->item(7,1)->text().toDouble();
    base.J_dv = ui->tableWidget->item(8,1)->text().toDouble();
    base.ki = ui->tableWidget->item(9,1)->text();

    if(ui->tableWidget->item(0,1)->text().isEmpty()||
            ui->tableWidget->item(1,1)->text().isEmpty()||
            ui->tableWidget->item(2,1)->text().isEmpty()||
            ui->tableWidget->item(3,1)->text().isEmpty()||
            ui->tableWidget->item(4,1)->text().isEmpty()||
            ui->tableWidget->item(5,1)->text().isEmpty()||
            ui->tableWidget->item(6,1)->text().isEmpty()||
            ui->tableWidget->item(7,1)->text().isEmpty()||
            ui->tableWidget->item(8,1)->text().isEmpty()||
            ui->tableWidget->item(9,1)->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
    }
    else
    {
    wf->zapis();
    wf->table();
    close();
    }
}

