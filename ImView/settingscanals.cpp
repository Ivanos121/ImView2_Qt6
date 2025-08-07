#include <QFileInfo>
#include <QSqlQuery>
#include <QSettings>

#include "settingscanals.h"
#include "ui_settingscanals.h"


int j=0;

SettingsCanals::SettingsCanals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsCanals)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(64);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Номер \n канала" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

//    for (int i=0; i<ui->tableWidget->rowCount(); i++)
//    {
//        if (ui->tableWidget->item(i, 0) != 0)
//        {
//            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Ток фазы А, А"));
//    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("Напряжение фазы А, В"));
//    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("Активная мошность фазы А, Вт"));
//    ui->tableWidget->setItem(3, 1, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));
//    ui->tableWidget->setItem(4, 1, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
//    ui->tableWidget->setItem(5, 1, new QTableWidgetItem("Коэффициент мощности фазы А"));
//    ui->tableWidget->setItem(6, 1, new QTableWidgetItem("Ток фазы В, А"));
//    ui->tableWidget->setItem(7, 1, new QTableWidgetItem("Напряжение фазы В, В"));
//    ui->tableWidget->setItem(8, 1, new QTableWidgetItem("Активная мошность фазы В, Вт"));
//    ui->tableWidget->setItem(9, 1, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
//    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
//    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Коэффициент мощности фазы В"));
//    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("Ток фазы С, А"));
//    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("Напряжение фазы С, В"));
//    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("Активная мошность фазы С, Вт"));
//    ui->tableWidget->setItem(15, 1, new QTableWidgetItem("Реактивная мошность фазы С, ВА"));
//    ui->tableWidget->setItem(16, 1, new QTableWidgetItem("Полная мошность фазы С, ВАР"));
//    ui->tableWidget->setItem(17, 1, new QTableWidgetItem("Коэффициент мощности фазы С"));
//    ui->tableWidget->setItem(18, 1, new QTableWidgetItem("трехфазная активная мошность, Вт"));
//    ui->tableWidget->setItem(19, 1, new QTableWidgetItem("Трехфазная реактивная мошность, ВА"));
//    ui->tableWidget->setItem(20, 1, new QTableWidgetItem("Трехфазная полная мошность, ВАР"));
//    ui->tableWidget->setItem(21, 1, new QTableWidgetItem("Коэффициент мощности"));
//    ui->tableWidget->setItem(22, 1, new QTableWidgetItem("Скорость вращения ротора, рад/с"));
//    ui->tableWidget->setItem(23, 1, new QTableWidgetItem("Момент, Н*м"));
//    ui->tableWidget->setItem(24, 1, new QTableWidgetItem("Момент сопротивления, Н*м"));

    QPalette p1=ui->tableWidget->palette();
    p1.setColor(QPalette::Base, QColor(225, 255, 255));
    p1.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p1);

    ui->tableWidget_2->setRowCount(11);
    ui->tableWidget_2->setColumnCount(3);
    QStringList name_2;
    name_2 << "Номер \n переменной" << "Номер \n выбранного канала" << "Величина";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_2->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<ui->tableWidget_2->rowCount(); i++)
    {
        if (ui->tableWidget_2->item(i, 0) != 0)
        {
            ui->tableWidget_2->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

//    ui->tableWidget_2->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
//    ui->tableWidget_2->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
//    ui->tableWidget_2->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
//    ui->tableWidget_2->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
//    ui->tableWidget_2->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
//    ui->tableWidget_2->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
//    ui->tableWidget_2->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
//    ui->tableWidget_2->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
//    ui->tableWidget_2->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
//    ui->tableWidget_2->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
//    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
//    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
//    ui->tableWidget_2->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
//    ui->tableWidget_2->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
//    ui->tableWidget_2->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
//    ui->tableWidget_2->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
//    ui->tableWidget_2->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p2=ui->tableWidget_2->palette();
    p2.setColor(QPalette::Base, QColor(225, 255, 255));
    p2.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_2->setPalette(p2);

    for(int i=0;i<64;i++)
    {
       // ui->tableWidget_2->setItem(i,1, ui->tableWiew->item(i, 2)->clone());
    }


//     sdb = QSqlDatabase::addDatabase("QSQLITE","Net_settings"); //объявление базы данных sqlite3
// //    if(QSqlDatabase::contains("Net_settings"))
// //    {
// //        sdb = QSqlDatabase::database("Net_settings");
// //    }
// //    else
// //    {
// //        sdb = QSqlDatabase::addDatabase("QSQLITE", "Net_settings");
// //    }

//     sdb.setDatabaseName(QFileInfo("../data/base_db/netdb2.db").absoluteFilePath()); //подключение к базе данных
//     sdb.open();

//     if(sdb.open())
//     {
//         qDebug() << "sdb opened OK...";
//     }else{
//         qDebug() << " sdb opening failed...";
//     }
    QSqlQuery query=QSqlQuery(sdb);

    if (query.exec("SELECT Id, Имя FROM Net_settings"))
    {
        for(int i = 0; query.next(); i++)
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(query.value(1).toString()));
        }

    }
    query.exec("SELECT Id, Имя FROM Net_settings");
    while (query.next())
    {
        int salary = query.value(0).toInt();
        QString name = query.value(1).toString();

        qDebug() << salary << name ;
    }

    if(query.exec("SELECT Id, Имя FROM Net_settings")){
        qDebug() << "query.exec opened OK...";
    }else{
        qDebug() << " query.exec opening failed...";
    }
    ui->tableWidget->resizeColumnsToContents();
    sdb.close();

    connect(ui->pushButton, &QPushButton::clicked,this, &SettingsCanals::dialog_close);
    connect(ui->pushButton_2, &QPushButton::clicked,this, &SettingsCanals::dialog_apply);
    connect(ui->pushButton_3, &QPushButton::clicked,this, &SettingsCanals::move_right);
    connect(ui->pushButton_4, &QPushButton::clicked,this, &SettingsCanals::move_left);
}


SettingsCanals::~SettingsCanals()
{
    delete ui;
}

void SettingsCanals::dialog_close()
{
    close();
}

void SettingsCanals::move_right()
{
    int i = ui->tableWidget->currentRow();
    ui->tableWidget_2->setItem(j,1, ui->tableWidget->item(i, 0)->clone());
    ui->tableWidget_2->setItem(j,2, ui->tableWidget->item(i, 1)->clone());
    j++;
}

void SettingsCanals::move_left()
{
    int g = ui->tableWidget_2->currentRow();
    for (int i = g; i < ui->tableWidget_2->rowCount() - 1; i++)
    {
        ui->tableWidget_2->item(i, 1)->setText(ui->tableWidget_2->item(i+1, 1)->text());
        ui->tableWidget_2->item(i, 2)->setText(ui->tableWidget_2->item(i+1, 2)->text());
    }
    j--;
}


void SettingsCanals::dialog_apply()
{
    QSettings settings;
    for (int i = 0; i < 11; i++)
    {
        settings.setValue(QString("ArchieverChannels/y")+ QString("%1").arg(i), ui->tableWidget_2->item(i, 1)->text());
    }
}

