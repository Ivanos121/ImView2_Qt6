#include "vent_settings.h"
#include "ui_vent_settings.h"

Vent_settings::Vent_settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_settings)
{
    ui->setupUi(this);
}

Vent_settings::~Vent_settings()
{
    delete ui;
}

void Vent_settings::on_pushButton_2_clicked()
{
    close();
}

