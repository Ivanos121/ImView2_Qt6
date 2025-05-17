#include <QMouseEvent>
#include <QSvgWidget>
#include <QHBoxLayout>

#include "mytablewidget_2.h"

MyTableWidget_2::MyTableWidget_2(QWidget *parent) : QTableWidget(parent)
{
    //setMouseTracking(true);
}

void MyTableWidget_2::enterEvent(QEnterEvent *event)
{
    QTableWidget::enterEvent(event);
    //QIcon hoverIcon("/home/elf/ImView2/data/img/system_icons/IM_96x96_elm_select.svg");  // Замените на путь к иконке при наведении
    //item(1, 2)->setIcon(hoverIcon);

    QWidget *widget = new QWidget();
    QSvgWidget *svgwidget = new QSvgWidget("/home/elf/ImView2/data/img/system_icons/IM_96x96_elm_select.svg");
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(svgwidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    setCellWidget(0, 0, widget);
}

void MyTableWidget_2::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    //QIcon icon("/home/elf/ImView2/data/img/system_icons/IM_96x96_elm.svg");  // Замените на путь к вашему изображению
    //item(1, 2)->setIcon(icon);
}


