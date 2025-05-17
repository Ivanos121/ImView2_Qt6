#include <QFileInfo>
#include <QIcon>

#include "draw_poper.h"
#include "ui_draw_poper.h"

draw_poper::draw_poper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_poper)
{
    ui->setupUi(this);
    ui->webEngineView_2->hide();
}

draw_poper::~draw_poper()
{
    delete ui;
}
