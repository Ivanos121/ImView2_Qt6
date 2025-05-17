#include <QDesktopServices>

#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    setCursor(Qt::PointingHandCursor);

}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}

void MyLabel::enterEvent(QEnterEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor)); // Изменяем курсор при наведении
    QLabel::enterEvent(event);
}

void MyLabel::leaveEvent(QEvent *event)
{
    unsetCursor(); // Возвращаем курсор по умолчанию
    QLabel::leaveEvent(event);
}
