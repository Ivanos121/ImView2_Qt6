#ifndef CUSTOMHELPDELEGATE_H
#define CUSTOMHELPDELEGATE_H

#include <QStyledItemDelegate>

class CustomHelpDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    CustomHelpDelegate(QObject *parent = 0);
    ~CustomHelpDelegate() override;

public slots:
    bool helpEvent( QHelpEvent* e, QAbstractItemView* view,
                   const QStyleOptionViewItem& option,
                   const QModelIndex& index ) override;
};

#endif // CUSTOMHELPDELEGATE_H
