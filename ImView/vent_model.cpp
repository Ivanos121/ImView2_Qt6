#include "vent_model.h"
#include "base.h"
#include "ui_vent_model.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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
    //QMessageBox::critical(this, "d", "d");
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
    for (int i = 0; i < 1000; i++)
    {
        model_el.rasch();
    }

    ui->plot->addPoint(0, model_el.t, model_el.omega);

    if (model_el.t > 10.0)
    {
        model_el.stop();
    }
}

void vent_model::vent_model_stop()
{
    model_el.stop();
}
