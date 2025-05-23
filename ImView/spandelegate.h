#ifndef SPANDELEGATE_H
#define SPANDELEGATE_H

#include <QStyledItemDelegate>
#include <QTreeView>

class SpanDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SpanDelegate(QTreeView *view, QObject *parent = nullptr);
    ~SpanDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;

private:
    bool shouldSpan(const QModelIndex &index) const;
    bool isPartOfSpan(const QModelIndex &index) const;
    QTreeView *m_view;
};

#endif // SPANDELEGATE_H
