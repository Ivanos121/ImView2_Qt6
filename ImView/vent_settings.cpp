#include <QMessageBox>

#include "vent_settings.h"
#include "ui_vent_settings.h"

Vent_settings::Vent_settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_settings)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked, this, &Vent_settings::apply_vent_dannie);
    connect(ui->pushButton_2,&QPushButton::clicked, this, &Vent_settings::close_vent_dannie);

    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setColumnCount(4);
    QStringList name_77;
    name_77 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget->setHorizontalHeaderLabels(name_77);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("b"));
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem("n"));
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem("ro"));
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem("S0"));
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem("S1"));
    ui->tableWidget->setItem(8, 1, new QTableWidgetItem("α1"));
    ui->tableWidget->setItem(9, 1, new QTableWidgetItem("S2"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("α2"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("S3"));
    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("S4"));
    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("φ"));
    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("φ2"));

    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(3, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget->setItem(4, 3, new QTableWidgetItem("кг/м3"));
    ui->tableWidget->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget->setItem(8, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(10, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget->setItem(11, 3, new QTableWidgetItem("м2"));
    ui->tableWidget->setItem(12, 3, new QTableWidgetItem("м2"));
    ui->tableWidget->setItem(13, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget->rowCount(); i++)
    {

        if (ui->tableWidget->item(i, 1) != 0)
        {
            ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,1) != 0)
        {
            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,2) != 0)
        {
            ui->tableWidget->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(row,3) != 0)
        {
            ui->tableWidget->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_13=ui->tableWidget->palette();
    p_13.setColor(QPalette::Base, QColor(255, 255, 191));
    p_13.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p_13);
}

Vent_settings::~Vent_settings()
{
    delete ui;
}

void Vent_settings::apply_vent_dannie()
{
    close();
    QMessageBox::information(this,tr("f"),tr("d"));
}

void Vent_settings::close_vent_dannie()
{
    close();
}

