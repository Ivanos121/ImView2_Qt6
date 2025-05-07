#include "tepl_identf.h"
#include "ui_tepl_identf.h"

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

    time=new QElapsedTimer();
}

Tepl_identf::~Tepl_identf()
{
    delete ui;
}
