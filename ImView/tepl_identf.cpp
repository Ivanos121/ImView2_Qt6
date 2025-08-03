#include "tepl_identf.h"
#include "ui_tepl_identf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model_el.h"

#include <QFileInfo>
#include <QSettings>

Model_el model_ell;
double keyy=0;
QTimer *timee;

Tepl_identf::Tepl_identf(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tepl_identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 3.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    timee = new QTimer(this);

    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/two_wase_tepl_model.html").absoluteFilePath()));
}

Tepl_identf::~Tepl_identf()
{
    delete ui;
}
void Tepl_identf::raschet_tepl_identf()
{
    wf->statusbar_label_9->setVisible(true);
    wf->statusbar_progres->setVisible(true);
    wf->statusbar_progres->setRange(0, 100);
    wf->statusbar_progres->reset();

    keyy = 0.0;

    connect(timee, &QTimer::timeout, this, &Tepl_identf::realtimeDataSlot);
    double Ts=0.000032;
    timee->start(Ts);

}

void Tepl_identf::realtimeDataSlot()
{

    // calculate two new data points:

    keyy = keyy+0.000032; // time elapsed since start of demo, in seconds

    double t = keyy;
    double maxTime = 0.1;
    wf->statusbar_progres->setValue(t / maxTime * 100);

    wf->statusbar_label_9->setText("T = " + QString::number(keyy,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    if (keyy>=0.1)
    {
        timee->stop();
        wf->ui->actionteplident_stop->setEnabled(false);
        wf->ui->actionteplident_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_3.svg"));

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

        wf->ui->lineEdit_7->setText(QString::number(0.5,'f',3));
        wf->ui->lineEdit_7->setAlignment(Qt::AlignCenter);
        wf->ui->lineEdit_19->setText(QString::number(0.4,'f',3));
        wf->ui->lineEdit_19->setAlignment(Qt::AlignCenter);
        wf->ui->lineEdit_20->setText(QString::number(0.07,'f',3));
        wf->ui->lineEdit_20->setAlignment(Qt::AlignCenter);

        wf->ui->stackedWidget->show();
        wf->ui->stackedWidget->setCurrentIndex(8);

        wf->statusbar_label_9->setVisible(false);
        wf->statusbar_progres->setVisible(false);
    }
}
