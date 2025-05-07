#include "vent_izm.h"
#include "ui_vent_izm.h"

#include <QFileInfo>
#include "plot.h"

vent_izm::vent_izm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_izm)
{
//    ui->setupUi(this);
//    ui->plot->t_max = 0.01;
//    ui->plot->U_max = 500.0;
//    ui->plot->margin_bottom = 40;
//    ui-plot->margin_left = 100;
//    ui->plot->reset();
}

vent_izm::~vent_izm()
{
    delete ui;
}
