#include "ostat_resurs.h"
#include "ui_ostat_resurs.h"
#include "plot.h"

Ostat_resurs::Ostat_resurs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ostat_resurs)
{
    ui->setupUi(this);
    ui->plots->t_max = 10.0;
    ui->plots->U_max = 3.0;
    ui->plots->margin_bottom = 40;
    ui->plots->margin_left = 100;
    ui->plots->reset();
}

Ostat_resurs::~Ostat_resurs()
{
    delete ui;
}
