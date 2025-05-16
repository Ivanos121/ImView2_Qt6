#ifndef SPANDELEGATE_H
#define SPANDELEGATE_H

#include <QStyledItemDelegate>
#include <QTreeView>


class SpanDelegate : public QStyledItemDelegate
{
public:
    SpanDelegate(QTreeView *view, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    bool shouldSpan(const QModelIndex &index) const;
    QTreeView *m_view;
};

#endif // SPANDELEGATE_H
