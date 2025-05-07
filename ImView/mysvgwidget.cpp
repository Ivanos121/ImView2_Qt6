#include "mysvgwidget.h"
#include <QHBoxLayout>
#include "start_app.h"
#include "ui_start_app.h"

MySvgWidget::MySvgWidget(QWidget *parent) : QSvgWidget(parent)
{


}

void MySvgWidget::enterEvent(QEnterEvent *)
{
    loadSelectedFile();
}

void MySvgWidget::leaveEvent(QEvent *)
{
    loadFile();
}

void MySvgWidget::loadFile()
{
    load(svgFileName);
}

void MySvgWidget::loadSelectedFile()
{
    load(svgSelectedFileName);
}


