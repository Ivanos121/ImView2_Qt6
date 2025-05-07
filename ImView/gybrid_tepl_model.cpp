#include "gybrid_tepl_model.h"
#include "ui_gybrid_tepl_model.h"

Gybrid_tepl_model::Gybrid_tepl_model(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gybrid_tepl_model)
{
    ui->setupUi(this);
    ui->plotg->t_max = 10.0;
    ui->plotg->U_max = 3.0;
    ui->plotg->margin_bottom = 40;
    ui->plotg->margin_left = 100;
    ui->plotg->reset();
}

Gybrid_tepl_model::~Gybrid_tepl_model()
{
    delete ui;
}
