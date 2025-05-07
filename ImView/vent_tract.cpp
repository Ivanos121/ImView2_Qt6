#include "vent_tract.h"
#include "ui_vent_tract.h"

#include <QFileInfo>
#include <QIcon>

Vent_tract::Vent_tract(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vent_tract)
{
    ui->setupUi(this);

    connect(ui->verticalSlider, &QSlider::valueChanged, this, &Vent_tract::on_speed);
    connect(ui->verticalSlider_2, &QSlider::valueChanged, this, &Vent_tract::on_moment);

//    ui->webEngineView_2->hide();
    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_var/vent_var.html").absoluteFilePath()));
    //ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

//    ui->tableWidget->setRowCount(12);
//    ui->tableWidget->setColumnCount(3);
//    QStringList name;
//    name << " № " << "Сигнал" << "Величина";
//    ui->tableWidget->setHorizontalHeaderLabels(name);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget->setColumnWidth(0, 100);

//    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
//    {
//        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
//        {
//            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

//        }
//    }

//    for (int i=0; i<12; i++)
//    {
//        if (ui->tableWidget->item(i, 0) != 0)
//        {
//            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    ui->tableWidget->setItem(0,  1, new QTableWidgetItem("Станина"));
//    ui->tableWidget->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади"));
//    ui->tableWidget->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
//    ui->tableWidget->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди"));
//    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
//    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Лобовая часть слева сзади"));
//    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Станина"));
//    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа спереди"));
//    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Лобовая часть справа сзади"));
//    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Магнитопровод статора"));
//    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел справа спереди"));
//    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Подшипниковый узел слева сзади"));

//    QPalette p99=ui->tableWidget->palette();
//    p99.setColor(QPalette::Base, QColor(225, 255, 255));
//    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
//    ui->tableWidget->setPalette(p99);

//    ui->tableWidget_2->setRowCount(12);
//    ui->tableWidget_2->setColumnCount(3);
//    QStringList name2;
//    name2 << " № " << "Сигнал" << "Величина";
//    ui->tableWidget_2->setHorizontalHeaderLabels(name);
//    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget_2->verticalHeader()->setVisible(false);
//    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget_2->setColumnWidth(0, 100);

//    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
//    {
//        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
//        {
//            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());

//        }
//    }

//    for (int i=0; i<12; i++)
//    {
//        if (ui->tableWidget_2->item(i, 0) != 0)
//        {
//            ui->tableWidget_2->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    ui->tableWidget_2->setItem(0,  1, new QTableWidgetItem("Станина"));
//    ui->tableWidget_2->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади"));
//    ui->tableWidget_2->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
//    ui->tableWidget_2->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди"));
//    ui->tableWidget_2->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
//    ui->tableWidget_2->setItem(5,  1, new QTableWidgetItem("Лобовая часть слева сзади"));
//    ui->tableWidget_2->setItem(6,  1, new QTableWidgetItem("Станина"));
//    ui->tableWidget_2->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа спереди"));
//    ui->tableWidget_2->setItem(8,  1, new QTableWidgetItem("Лобовая часть справа сзади"));
//    ui->tableWidget_2->setItem(9,  1, new QTableWidgetItem("Магнитопровод статора"));
//    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел справа спереди"));
//    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem("Подшипниковый узел слева сзади"));

//    QPalette p101=ui->tableWidget_2->palette();
//    p101.setColor(QPalette::Base, QColor(225, 255, 255));
//    p101.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
//    ui->tableWidget_2->setPalette(p101);
}

Vent_tract::~Vent_tract()
{
    delete ui;
}

void Vent_tract::on_speed(int value)
{
   // ui->label_3->setText(QString::number(0));
    //ui->verticalSlider->setRange(0, 99);
    //ui->verticalSlider->setValue(value);

    speed = value / 99.0 * 157.0;
   // ui->label_3->setText(QString::number(speed));
//    ui->label_3->setText(QString("%1 speed").arg(speed, 0, 'f', 1));

}

void Vent_tract::on_moment(int value)
{
   // ui->label_3->setText(QString::number(0));
    //ui->verticalSlider->setRange(0, 99);
    //ui->verticalSlider->setValue(value);

    moment = value / 99.0 * 30.0;
//    ui->label_4->setText(QString::number(moment));
//    ui->label_4->setText(QString("%1 moment").arg(moment, 0, 'f', 1));
}
