#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include "qstyleditemdelegate.h"

#include <QTreeView>

class LineDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    using PaintFunction = std::function<void(QPainter*, const QStyleOptionViewItem&, const QModelIndex&)>;
    explicit LineDelegate(QTreeView *view,QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
private:
    QTreeView *m_view;
    void m_paintFunc2(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void m_paintFunc1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void m_paintFunc3(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void m_paintFunc4(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;


    bool shouldSpan(const QModelIndex &index) const;
    bool isPartOfSpan(const QModelIndex &index) const;
    int getItemLevel(const QModelIndex &index) const;
    bool isItemLast(const QModelIndex &index, int level) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // LINEDELEGATE_H
