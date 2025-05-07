#include "vent_identf.h"
#include "ui_vent_identf.h"

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
}

Vent_identf::~Vent_identf()
{
    delete ui;
}
