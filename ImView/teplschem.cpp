#include "teplschem.h"
#include "ui_teplschem.h"

#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

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



