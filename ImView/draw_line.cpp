#include "draw_line.h"
#include "ui_draw_line.h"

#include <QFileInfo>
#include <QIcon>
#include <QString>

draw_line::draw_line(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_line)
{
    ui->setupUi(this);

    ui->webEngineView_2->hide();
}

draw_line::~draw_line()
{
    delete ui;
}
