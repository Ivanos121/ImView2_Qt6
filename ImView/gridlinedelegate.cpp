#include <QPainter>

#include "gridlinedelegate.h"
/*
GridLineDelegate::GridLineDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

GridLineDelegate::~GridLineDelegate()
{

}

void GridLineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    if (index.isValid())
    {
        painter->setPen(Qt::SolidLine);
        painter->setPen(QColor(Qt::lightGray));

        painter->drawLine(QLine(option.rect.bottomLeft(), option.rect.bottomRight()));
        painter->drawLine(QLine(option.rect.topRight(), option.rect.bottomRight()));
    }
}
*/
