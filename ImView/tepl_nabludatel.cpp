#include "tepl_nabludatel.h"
#include "ui_tepl_nabludatel.h"
#include "plot.h"

tepl_nabludatel::tepl_nabludatel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tepl_nabludatel)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 500.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();
}

tepl_nabludatel::~tepl_nabludatel()
{
    delete ui;
}
