#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

#include "teplschem.h"
#include "ui_teplschem.h"

teplschem::teplschem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teplschem)
{
    ui->setupUi(this);
}

teplschem::~teplschem()
{
    delete ui;
}



