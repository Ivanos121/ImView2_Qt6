#include "vent_identf.h"
#include "ui_vent_identf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>

double keys = 0.0;
QTimer *times;
static bool isFinished;

Vent_identf::Vent_identf(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 3.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    times = new QTimer(this);

    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html")
                                                      .absoluteFilePath()));
}

Vent_identf::~Vent_identf()
{
    delete ui;
}

void Vent_identf::raschet_vent_identf()
{
    isFinished = false;
    wf->statusbar_label_9->setVisible(true);
    wf->statusbar_progres->setVisible(true);
    wf->statusbar_progres->setRange(0, 100);
    wf->statusbar_progres->reset();
    isFinished = false;
    if (times->isActive())
    {
        times->stop();
    }
    keys = 0.0;

    connect(times, &QTimer::timeout, this, &Vent_identf::realtimeDataSlot);
    double Ts=0.000032;
    times->start(Ts);
}

void Vent_identf::realtimeDataSlot()
{

    // calculate two new data points:

    keys = keys+0.000032; // time elapsed since start of demo, in seconds

    double t = keys;
    double maxTime = 0.1;
    wf->statusbar_progres->setValue(t / maxTime * 100);

    wf->statusbar_label_9->setText("T = " + QString::number(keys,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    if (keys>=0.1&& !isFinished)
    {
        isFinished = true;
        if (times->isActive())
        {
            times->stop();
        }
        wf->ui->vent_identf_stop->setEnabled(false);
        wf->ui->ventidentf_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_4.svg"));

        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        QString lokal = settings.value( "Messages", "").toString();
        settings.endGroup();

        if(lokal == "fix")
        {
            QMessageBox::information(this, tr("Сообщение"), tr("Расчет параметров тепловой схемы замещения закончен"));
        }
        else if(lokal == "nonfix")
        {
            QString summary_s = "Сообщение";
            QString body_s = "Расчет параметров тепловой схемы замещения закончен";
            wf->message_action(summary_s, body_s);
        }

        // wf->ui->lineEdit_7->setText(QString::number(0.5,'f',3));
        // wf->ui->lineEdit_7->setAlignment(Qt::AlignCenter);
        // wf->ui->lineEdit_19->setText(QString::number(0.4,'f',3));
        // wf->ui->lineEdit_19->setAlignment(Qt::AlignCenter);
        // wf->ui->lineEdit_20->setText(QString::number(0.07,'f',3));
        // wf->ui->lineEdit_20->setAlignment(Qt::AlignCenter);

        wf->ui->stackedWidget->show();
        wf->ui->stackedWidget->setCurrentIndex(8);

        wf->statusbar_label_9->setVisible(false);
        wf->statusbar_progres->setVisible(false);
    }
}
