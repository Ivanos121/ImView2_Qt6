#include "vent_model.h"
#include "ui_vent_model.h"

vent_model::vent_model(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_model)
{
    ui->setupUi(this);
}

vent_model::~vent_model()
{
    delete ui;
}

