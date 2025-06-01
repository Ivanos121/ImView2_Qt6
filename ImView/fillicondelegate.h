#ifndef FILLICONDELEGATE_H
#define FILLICONDELEGATE_H

#include <QStyledItemDelegate>


class FillIconDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FillIconDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // FILLICONDELEGATE_H
