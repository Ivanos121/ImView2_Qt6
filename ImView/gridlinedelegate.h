#ifndef GRIDDELEGATE_H
#define GRIDDELEGATE_H

#include <QSize>
#include <QStyledItemDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class GridLineDelegate : public QStyledItemDelegate
{
public:
    GridLineDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

};

#endif
