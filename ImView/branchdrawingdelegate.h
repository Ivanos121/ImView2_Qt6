#ifndef BRANCHDRAWINGDELEGATE_H
#define BRANCHDRAWINGDELEGATE_H

#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QTreeView>

class BranchDrawingDelegate : public QStyledItemDelegate
{

public:
    explicit BranchDrawingDelegate(QTreeView *view,QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
private:
    QTreeView *m_view;
    void drawParallelLine(QPainter *painter, const QPoint &start, const QPoint &end) const;
    mutable QVector<QModelIndex> m_rootIndices;

    void populateRootIndices() const;
};

#endif // BRANCHDRAWINGDELEGATE_H
