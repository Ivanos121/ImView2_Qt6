#include "vent_model.h"
#include "base.h"
#include "ui_vent_model.h"
#include "ui_mainwindow.h"
#include "ui_datas.h"
#include "Base_tepl_vent.h"
#include "vent_identf.h"
#include "polynomial.h"

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
    ui->plot->addDataLine(QColor(255,100,100), 0);
    ui->plot->addDataLine(QColor(255,100,100), 0);
    ui->plot->addDataLine(QColor(255,100,100), 0);

    base.R1 = wf->ui->lineEdit_12->text().toDouble();
    base.R2 = wf->ui->lineEdit_11->text().toDouble();
    base.L1 = wf->ui->lineEdit_10->text().toDouble();
    base.L2 = wf->ui->lineEdit_9->text().toDouble();
    base.Lm = wf->ui->lineEdit_8->text().toDouble();

    QModelIndex myIndex;
    myIndex = wf->ui->widget->ui->tableView->model()->index(wf->ui->widget->ui->tableView->currentIndex().row(), 4, QModelIndex());
    base.U_fnom=wf->ui->widget->ui->tableView->model()->data(myIndex).toDouble();
    myIndex = wf->ui->widget->ui->tableView->model()->index(wf->ui->widget->ui->tableView->currentIndex().row(), 9, QModelIndex());
    base.J_dv=wf->ui->widget->ui->tableView->model()->data(myIndex).toDouble();

    model_el.init_el(base.R1, base.R2, base.L1, base.L2, base.Lm, "Режим S1",
                     0,
                     0,
                     Model_el::DIRECT_START);

    if(wf->time_base_selection_value->text() == "Текущее время")
    {
        wf->statusbar_label_9->setVisible(true);
        wf->statusbar_progres->setVisible(true);
        wf->statusbar_progres->setRange(0, 0);
        wf->statusbar_progres->reset();
    }
    else if(wf->time_base_selection_value->text() == "Фиксированное время")
    {
        wf->statusbar_label_9->setVisible(true);
        wf->statusbar_progres->setVisible(true);
        wf->statusbar_progres->setRange(0, 100);
        wf->statusbar_progres->reset();
    }
}

void vent_model::modelReady()
{
    base.Mc_n = wf->ui->horizontalSlider_4->value();
    base.Um = wf->ui->horizontalSlider_3->value();

    for (int i = 0; i < 1000; i++)
    {
        model_el.rasch();

    }

    // Создание экземпляров полиномов
    Polynomial w_Q_inv_poly(ventparam.w_Q_inv_koeffss);
    Polynomial Q_H1_poly(ventparam.Q_H1_koeffss);
    Polynomial Q_H2_poly(ventparam.Q_H2_koeffss);
    Polynomial Q_Pv_poly(ventparam.Q_Pv_koeffss);

    double tt = model_el.t;
    int maxTime = wf->time_work_value->text().toInt();

    wf->statusbar_progres->setValue((double)tt / (double)maxTime * 100.0);
    wf->statusbar_label_9->setText("T = " + QString::number(model_el.t,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    // Q_appr[i] = w_Q_inv_poly.evaluate(w[i]);
    // H1_appr[i] = Q_H1_poly.evaluate(Q_appr[i]);
    // H2_appr[i] = Q_H2_poly.evaluate(Q_appr[i]);
    // Pv_appr[i] = Q_Pv_poly.evaluate(Q_appr[i]);

    //Расчет и вывод на plot omega and Qappr
    double evaluatedQ = w_Q_inv_poly.evaluate(model_el.omega);
    ventparam.Q_appr.append(evaluatedQ);

    //ui->plot->addPoint(0, 0, model_el.omega);
    ui->plot->addPoint(0, tt, model_el.omega);

    //ui->plot->addPoint(1, 0, evaluatedQ);
    ui->plot->addPoint(1, tt, evaluatedQ*1000);

    double evaluatedH1;
    double evaluatedH2;
    double evaluatedH3;

    //Расчет и вывод на plot H1appr
    for (int i = 0; i < ventparam.Q_appr.size(); ++i)
    {
        evaluatedH1 = Q_H1_poly.evaluate(ventparam.Q_appr[i]);
        ventparam.H1_appr.append(evaluatedH1);
    }

    //ui->plot->addPoint(2, 0, evaluatedH1);
    ui->plot->addPoint(2, tt, evaluatedH1);

    //Расчет и вывод на plot H2appr
    for (int i = 0; i < ventparam.Q_appr.size(); ++i)
    {
        evaluatedH2 = Q_H2_poly.evaluate(ventparam.Q_appr[i]);
        ventparam.H2_appr.append(evaluatedH2);
    }

    //ui->plot->addPoint(3, 0, evaluatedH2);
    ui->plot->addPoint(3, tt, evaluatedH2);

    //Расчет и вывод на plot Pv_appr
    for (int i = 0; i < ventparam.Q_appr.size(); ++i)
    {
        evaluatedH3 = Q_H2_poly.evaluate(ventparam.Q_appr[i]);
        ventparam.Pv_appr.append(evaluatedH3);
    }

    ui->plot->addPoint(4, 0, evaluatedH3);
    ui->plot->addPoint(4, tt, evaluatedH3);

    if(wf->time_base_selection_value->text() == "Фиксированное время")
    {
        if (model_el.t > wf->time_work_value->text().toDouble())
        {
            vent_model_stop();
        }
    }
}

void vent_model::vent_model_stop()
{
    model_el.stop();
    wf->statusbar_label_9->setVisible(false);
    wf->statusbar_progres->setVisible(false);
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
