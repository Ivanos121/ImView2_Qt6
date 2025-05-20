#ifndef GRIDDELEGATE_H
#define GRIDDELEGATE_H

#include <QSize>
#include <QStyledItemDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class GridLineDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit GridLineDelegate(QObject *parent= nullptr);
    ~GridLineDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif
