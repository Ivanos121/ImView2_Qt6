#ifndef CMYDELEGATE_H
#define CMYDELEGATE_H

#include "qstyleditemdelegate.h"

class CMyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CMyDelegate(QObject* parent= nullptr);
    ~CMyDelegate() override;
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
};

#endif // CMYDELEGATE_H
