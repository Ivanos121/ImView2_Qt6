#include <iostream>
#include <fstream>
#include <cfloat>
#include <QLinearGradient>
#include <QColorDialog>
#include <cmath>
#include <QSpinBox>
#include <QSettings>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusVariant>
#include <QDBusReply>
#include <QDBusInterface>

#include "datasource_el.h"
#include "datasource_file.h"
#include "datasourcebvas.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identf.h"
#include "ui_identf.h"
#include "model.h"
#include "plot.h"
#include "base.h"
#include "spinboxdelegate.h"

double key;
Model model;
Modell modell;
//const double R1=2.419;
int count = 0;
static double minR2, maxR2, middleR2;
//double P_nom, n_nom, U_fnom, cosf_nom, kpd_nom, muk, n_0;

identf::identf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 3.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    time=new QElapsedTimer();
    this->showMaximized();


    ui->tableWidget->setRowCount(4); //задание количества строк таблицы
    ui->tableWidget->setColumnCount(6); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Смещение" << "Масштаб" << "Значение"; //перечисление заголовков
    ui->tableWidget->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->resizeColumnsToContents();
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    QTableWidgetItem *item252 = new QTableWidgetItem("Item252");
    item252->setCheckState(Qt::Checked);
    item252->setText("Сопротивление ротора R2, Ом");
    ui->tableWidget->setItem(0, 2, item252);

    QTableWidgetItem *item253 = new QTableWidgetItem("Item253");
    item253->setCheckState(Qt::Checked);
    item253->setText("Индуктивность обмотки статора L1, Гн");
    ui->tableWidget->setItem(1, 2, item253);

    QTableWidgetItem *item254 = new QTableWidgetItem("Item254");
    item254->setCheckState(Qt::Checked);
    item254->setText("Индуктивность обмотки ротора L2, Гн");
    ui->tableWidget->setItem(2, 2, item254);

    QTableWidgetItem *item255 = new QTableWidgetItem("Item254");
    item255->setCheckState(Qt::Checked);
    item255->setText("Индуктивность взаимоиндукции Lm, Гн");
    ui->tableWidget->setItem(3, 2, item255);

    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(1, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(2, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(3, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(3, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(4, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(4, 5, new QTableWidgetItem(QString("%1").arg(0)));

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }


    for (int i=0; i < ui->tableWidget->rowCount(); i++)
    {
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget->item(i, 4) != 0)
        {
            ui->tableWidget->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget->item(i, 5) != 0)
        {
            ui->tableWidget->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        }
    }


    SpinBoxDelegate *spin = new SpinBoxDelegate(ui->tableWidget); //создание делегата для создания комбобоксов
    ui->tableWidget->setItemDelegateForColumn(3, spin);
    SpinBoxDelegate *spin2 = new SpinBoxDelegate(ui->tableWidget); //создание делегата для создания комбобоксов
    ui->tableWidget->setItemDelegateForColumn(4, spin2);

    QPalette p4=ui->tableWidget->palette();
    p4.setColor(QPalette::Base, QColor(225, 255, 255));
    p4.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p4);

    dataLineColors_identf.append(Qt::red);
    dataLineColors_identf.append(Qt::green);
    dataLineColors_identf.append(Qt::cyan);
    dataLineColors_identf.append(Qt::yellow);

    for (int i = 0; i < dataLineColors_identf.size(); i++)
    {
        ui->tableWidget->item(i, 1)->setBackground(dataLineColors_identf[i]);
    }

    connect(ui->tableWidget, &QTableWidget::cellClicked,this, &identf::setcolorincell);
    connect(ui->tableWidget, &QTableWidget::cellChanged,this, &identf::edit_graf);


}

identf::~identf()
{
    delete ui;
}

void identf::realtimeDataSlot()
{
    wf->statusbar_label_9->setVisible(true);
    wf->statusbar_progres->setVisible(true);
    wf->statusbar_progres->setRange(0, 0);
    wf->statusbar_progres->reset();
    // calculate two new data points:
    key = time->elapsed()/1000.0; // time elapsed since start of demo, in seconds

    qDebug() << key;
    model.rasch(dataSource);

    // int t = wf->ui->widget_3->key;
    // int maxTime = wf->item174->text().toInt();

    wf->statusbar_label_9->setText("T = " + QString::number(key,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    //wf->statusbar_progres->setValue(t / maxTime * 100);

    if (model.R2 > maxR2)
           {
               maxR2 = model.R2;
           }

           if (model.R2 < minR2)
           {
               minR2 = model.R2;
           }

           middleR2 += model.R2;
           count++;

   if (count == 3)
   {
       middleR2 /= count;

       count = 0;

       if (fabs((maxR2 - minR2)/middleR2) < 0.006)
       {
            dataSource->stop();
            wf->ui->identf_stop->setEnabled(false);
            wf->ui->identf_pusk->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));

          //  wf->statusbar_label_9->setVisible(false);
            wf->statusbar_progres->setVisible(false);

            QSettings settings( "BRU", "IM View");
            settings.beginGroup( "System_messages" );
            QString lokal = settings.value( "Messages", "").toString();
            settings.endGroup();

            if(lokal == "fix")
            {
                QMessageBox::information(this, tr("Сообщение"), tr("Расчет параметров схемы замещения закончен"));
            }
            else if(lokal == "nonfix")
            {
                QString summary_s = "Сообщение";
                QString body_s = "Расчет параметров схемы замещения закончен";
                wf->message_action(summary_s, body_s);
            }
                wf->ui->stackedWidget->show();
            wf->ui->stackedWidget->setCurrentIndex(1);
       }
       minR2 = DBL_MAX;
       maxR2 = -DBL_MAX;
       middleR2 = 0.0;
   }

   //if (count % 100 == 0)
   if (true)
   {
        ui->plot->addPoint(0, key, model.R2);
        ui->plot->addPoint(1, key, model.L);
        ui->plot->addPoint(2, key, model.L);
        ui->plot->addPoint(3, key, model.Lm);

        std::ofstream fout;

        fout.open(QString(base.identfFilename).toStdString(),std::ios::out | std::ios::app);

        fout << QString("%1").arg(key).toStdString() << ";";
        fout << QString("%1").arg(model.R2).toStdString() << ";";
        fout << QString("%1").arg(model.L).toStdString() << ";";
        fout << QString("%1").arg(model.L).toStdString() << ";";
        fout << QString("%1").arg(model.Lm).toStdString() << ";";

        fout << std::endl;

        fout.close();

        wf->ui->lineEdit_12->setText(QString::number(model.R1,'f',3));
        wf->ui->lineEdit_11->setText(QString::number(model.R2,'f',3));
        wf->ui->lineEdit_10->setText(QString::number(model.L,'f',3));
        wf->ui->lineEdit_9->setText(QString::number(model.L,'f',3));
        wf->ui->lineEdit_8->setText(QString::number(model.Lm,'f',3));
    }
}

void identf::raschet_f()
{
    minR2 = DBL_MAX;
    maxR2 = -DBL_MAX;
    middleR2 = 0.0;

   // auto uiDatasWindow = wf->ui->widget->ui;

    //Режим Осциллограф
    if(wf->identification_switch_value->text() == "Осциллограф")
    {
        dataSource = new DataSourceBVAS();
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    //Режим Внутренний источник данных
    if (wf->identification_switch_value->text() == "Внутренний источник данных")
    {
        dataSource = new DataSource_el(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    if(wf->identification_switch_value->text() == "Чтение данных из файла для идентификации параметров схемы замещения")
    {
        QString dataSourceFileName = wf->load_data_ruchn_identf_value->text();
        base.dataSourceFilename = dataSourceFileName;
        dataSource = new DataSource_file();
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    dataSource->init();
    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0,
               wf->ui->lineEdit_13->text().toDouble(),wf->ui->lineEdit_14->text().toDouble(),wf->ui->lineEdit_15->text().toDouble(),
               wf->ui->lineEdit_16->text().toDouble(),wf->ui->lineEdit_17->text().toDouble(),wf->ui->lineEdit_18->text().toDouble());
    ui->plot->clear();

    for (int i = 0; i < 4; i++)
    {
        ui->plot->addDataLine(dataLineColors_identf[i], 0);
    }

    ui->plot->addPoint(0, 0, model.R2);
    ui->plot->addPoint(1, 0, model.L);
    ui->plot->addPoint(2, 0, model.L);
    ui->plot->addPoint(3, 0, model.Lm);


    if(wf->calculation_mode_value->text() == "Автоматический")
    {
        wf->ui->lineEdit_13->setText("0.01");
        wf->ui->lineEdit_16->setText("0.1");
        wf->ui->lineEdit_14->setText("0.05");
        wf->ui->lineEdit_17->setText("0.02");
        wf->ui->lineEdit_15->setText("0.01");
        wf->ui->lineEdit_18->setText("0.0001");
        wf->ui->lineEdit_13->setReadOnly(true);
        wf->ui->lineEdit_16->setReadOnly(true);
        wf->ui->lineEdit_14->setReadOnly(true);
        wf->ui->lineEdit_17->setReadOnly(true);
        wf->ui->lineEdit_15->setReadOnly(true);
        wf->ui->lineEdit_18->setReadOnly(true);
    }
    else
    {
        wf->ui->lineEdit_13->setReadOnly(false);
        wf->ui->lineEdit_16->setReadOnly(false);
        wf->ui->lineEdit_14->setReadOnly(false);
        wf->ui->lineEdit_17->setReadOnly(false);
        wf->ui->lineEdit_15->setReadOnly(false);
        wf->ui->lineEdit_18->setReadOnly(false);
    }
    ui->plot->addPoint(0, key, model.R2);
    ui->plot->addPoint(1, key, model.L);
    ui->plot->addPoint(2, key, model.L);
    ui->plot->addPoint(3, key, model.Lm);

    ui->tableWidget->item(0,5)->setText(QString::number(model.R2,'f',3));
    ui->tableWidget->item(1,5)->setText(QString::number(model.L,'f',3));
    ui->tableWidget->item(2,5)->setText(QString::number(model.L,'f',3));
    ui->tableWidget->item(3,5)->setText(QString::number(model.Lm,'f',3));

    std::ofstream fout;

    fout.open(QString(base.identfFilename).toStdString(),std::ios::out | std::ios::app);

    fout << QString("%1").arg(key).toStdString() << ";";
    fout << QString("%1").arg(model.R2).toStdString() << ";";
    fout << QString("%1").arg(model.L).toStdString() << ";";
    fout << QString("%1").arg(model.L).toStdString() << ";";
    fout << QString("%1").arg(model.Lm).toStdString() << ";";

    fout << std::endl;

    fout.close();

    time->start();
}

void identf::setcolorincell(int row, int column)
{
    if ((column == 1) && (row >= 0) && (row <= 5))
    {
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user

        if (chosenColor.isValid()) {
            ui->tableWidget->item(row, column)->setBackground(chosenColor);
            ui->plot->setDataLineColor(row, chosenColor);
            dataLineColors_identf[row] = chosenColor;
            repaint();
        }
        // Если пользователь нажал "Отмена", ничего не делаем
    }
}

void identf::edit_graf()
{
    double R2_scale, R2_offset, L1_scale, L1_offset, L2_scale, L2_offset, Lm_scale, Lm_offset;
    R2_scale = ui->tableWidget->item(0,4)->text().toDouble();
    R2_offset = ui->tableWidget->item(0,3)->text().toDouble();
    L1_scale = ui->tableWidget->item(1,4)->text().toDouble();
    L1_offset = ui->tableWidget->item(1,3)->text().toDouble();
    L2_scale = ui->tableWidget->item(2,4)->text().toDouble();
    L2_offset = ui->tableWidget->item(2,3)->text().toDouble();
    Lm_scale = ui->tableWidget->item(3,4)->text().toDouble();
    Lm_offset = ui->tableWidget->item(3,3)->text().toDouble();

    ui->plot->setDataLineOffset(0, R2_offset);
    ui->plot->setDataLineScale(0, R2_scale);
    ui->plot->setDataLineOffset(1, L1_offset);
    ui->plot->setDataLineScale(1, L1_scale);
    ui->plot->setDataLineOffset(2, L2_offset);
    ui->plot->setDataLineScale(2, L2_scale);
    ui->plot->setDataLineOffset(3, Lm_offset);
    ui->plot->setDataLineScale(3, Lm_scale);

    if (ui->tableWidget->item(0,2)->checkState())
    {
        ui->plot->enableDataLine(0, true);
    }
    else
    {
        ui->plot->enableDataLine(0, false);
    }

    if (ui->tableWidget->item(1,2)->checkState())
    {
        ui->plot->enableDataLine(1, true);
    }
    else
    {
        ui->plot->enableDataLine(1, false);
    }

    if (ui->tableWidget->item(2,2)->checkState())
    {
        ui->plot->enableDataLine(2, true);
    }
    else
    {
        ui->plot->enableDataLine(2, false);
    }

    if (ui->tableWidget->item(3,2)->checkState())
    {
        ui->plot->enableDataLine(3, true);
    }
    else
    {
        ui->plot->enableDataLine(3, false);
    }

    ui->tableWidget->item(0,5)->setText(QString::number((model.R2 + R2_offset)*R2_scale,'f',3));
    ui->tableWidget->item(1,5)->setText(QString::number((model.L + L1_offset)*L1_scale,'f',3));
    ui->tableWidget->item(2,5)->setText(QString::number((model.L + L2_offset)*L2_scale,'f',3));
    ui->tableWidget->item(3,5)->setText(QString::number((model.Lm + Lm_offset)*Lm_scale,'f',3));

    ui->plot->repaint();
}












