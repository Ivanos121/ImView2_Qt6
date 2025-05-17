#include <QMessageBox>

#include "vent_settings.h"
#include "ui_vent_settings.h"

Vent_settings::Vent_settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_settings)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked, this, &Vent_settings::apply_vent_dannie);
    connect(ui->pushButton_2,&QPushButton::clicked, this, &Vent_settings::close_vent_dannie);
}

Vent_settings::~Vent_settings()
{
    delete ui;
}

void Vent_settings::apply_vent_dannie()
{
    close();
    QMessageBox::information(this,tr("f"),tr("d"));
}

void Vent_settings::close_vent_dannie()
{
    close();
}

