#include <QHBoxLayout>

#include "mysvgwidget.h"

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


