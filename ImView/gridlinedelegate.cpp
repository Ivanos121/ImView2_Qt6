#include "gridlinedelegate.h"
#include "qpainter.h"

//#include <QtGui>

GridLineDelegate::GridLineDelegate(QObject* parent)
  : QStyledItemDelegate(parent)
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
