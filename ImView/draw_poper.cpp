#include "draw_poper.h"
#include "ui_draw_poper.h"

#include <QFileInfo>
#include <QIcon>

//double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11;

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
