#ifndef CMYDELEGATE_H
#define CMYDELEGATE_H

#include "qstyleditemdelegate.h"
class CMyDelegate : public QStyledItemDelegate
{
public:
    CMyDelegate(QObject* parent= nullptr);    
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
};

#endif // CMYDELEGATE_H
