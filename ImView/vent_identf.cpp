#include "vent_identf.h"
#include "ui_vent_identf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base.h"

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

    dataLineColors_vent_identf.append(Qt::red);
    dataLineColors_vent_identf.append(Qt::green);

    // for (int i = 0; i < dataLineColors_vent_identf.size(); i++)
    // {
    //     ui->tableWidget->item(i, 1)->setBackground(dataLineColors_vent_identf[i]);
    // }

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
    wf->loadMotorParameters();
               // >tableWidget->item(0,1)->text();
    // base.P_nom = ui->tableWidget->item(1,1)->text().toDouble();
    // base.n_nom = ui->tableWidget->item(2,1)->text().toDouble();
    // base.U_fnom = ui->tableWidget->item(3,1)->text().toDouble();
    // base.cosf_nom = ui->tableWidget->item(4,1)->text().toDouble();
    // base.kpd_nom = ui->tableWidget->item(5,1)->text().toDouble();
    // base.muk = ui->tableWidget->item(6,1)->text().toDouble();
    // base.n_0 = ui->tableWidget->item(7,1)->text().toDouble();
    // base.J_dv = ui->tableWidget->item(8,1)->text().toDouble();
    // base.ki = ui->tableWidget->item(9,1)->text();

    double w_0 = 2*3.14*base.n_0/60;
    double w_nom = 2*3.14*base.n_nom/60;
    double M_nom = base.P_nom/w_nom;
    double M_kr = M_nom*base.muk;
    double s_nom = (w_0-w_nom)/w_0;
    double s_kr = (sqrt(s_nom)+sqrt(((base.muk)-1)/(base.muk/20)-1))/((1/sqrt(s_nom))+sqrt(((base.muk)-1)/(base.muk/20)-1));
    double qq=((1/sqrt(s_kr))-sqrt(s_kr));
    double q = ((pow(qq,2)/((base.muk/20)-1)))-2;

    int N = 100; // количество точек
    QVector<double> w(N);
    QVector<double> M(N);

    double s_min = 0.0;
    double s_max = 1.0;
    double step = (s_max - s_min) / (N - 1);

    ui->plot->clear();

    for (int i = 0; i < 2; i++)
    {
        ui->plot->addDataLine(dataLineColors_vent_identf[i], 0);
    }

    for (int s_idx = 0; s_idx < N; ++s_idx)
    {
        double s = s_min + s_idx * step;
        w[s_idx] = w_0 * (1 - s);
        M[s_idx] = (M_kr * (2 + q)) / ((s / s_kr) + (s_kr / s) + q);
        ui->plot->addPoint(0, s, w[s_idx]);
        ui->plot->addPoint(1, s, M[s_idx]);

    }


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
