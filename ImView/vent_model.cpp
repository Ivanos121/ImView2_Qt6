#include "vent_model.h"
#include "base.h"
#include "ui_vent_model.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSettings>

vent_model::vent_model(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_model)
{
    ui->setupUi(this);
    ui->plot->t_max = 12.0;
    ui->plot->U_max = 200.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->clear();

    connect(&model_el, &Model_el::ready, this, &vent_model::modelReady);
}

vent_model::~vent_model()
{
    delete ui;
}

void vent_model::vent_model_start()
{
    ui->plot->clear();
    ui->plot->addDataLine(QColor(255,0,0), 0);

    base.R1 = wf->ui->lineEdit_12->text().toDouble();
    base.R2 = wf->ui->lineEdit_11->text().toDouble();
    base.L1 = wf->ui->lineEdit_10->text().toDouble();
    base.L2 = wf->ui->lineEdit_9->text().toDouble();
    base.Lm = wf->ui->lineEdit_8->text().toDouble();

    model_el.init_el(base.R1, base.R2, base.L1, base.L2, base.Lm, "Режим S1",
                     0,
                     0,
                     Model_el::DIRECT_START);


}

void vent_model::modelReady()
{
    wf->statusbar_label_9->setVisible(true);
    wf->statusbar_progres->setVisible(true);
    wf->statusbar_progres->setRange(0, 100);
    wf->statusbar_progres->reset();

    base.Mc_n = wf->ui->horizontalSlider_4->value();
    base.Um = wf->ui->horizontalSlider_3->value();

    for (int i = 0; i < 1000; i++)
    {
        model_el.rasch();
    }

    double tt = model_el.t;
    //qDebug() << tt;
    int maxTime = wf->time_work_value->text().toInt();

    wf->statusbar_progres->setValue((double)tt / (double)maxTime * 100.0);
    wf->statusbar_label_9->setText("T = " + QString::number(model_el.t,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    ui->plot->addPoint(0, model_el.t, model_el.omega);

    if(wf->time_base_selection_value->text() == "Текущее время")
    {
        if (model_el.t > 10.0)
        {
            model_el.stop();
            wf->ui->pushButton_8->setEnabled(false);

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
        }
    }
    else if(wf->time_base_selection_value->text() == "Фиксированное время")
    {
        if (model_el.t > wf->time_work_value->text().toDouble())
        {
            model_el.stop();
            wf->ui->pushButton_8->setEnabled(false);

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
        }
    }
}

void vent_model::vent_model_stop()
{
    model_el.stop();
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
}
