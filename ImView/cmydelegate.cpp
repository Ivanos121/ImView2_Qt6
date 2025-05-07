#include "cmydelegate.h"
#include "qapplication.h"
#include "qpainter.h"

CMyDelegate::CMyDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

//void CMyDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
void CMyDelegate:: paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString item_color;
    if (index.column() == 1 && index.row()==1)
    {
        item_color = "BLUE";
    } else{
        item_color = "RED";
    }
    QStyleOptionViewItem s = *qstyleoption_cast<const QStyleOptionViewItem*>(&option);
    s.palette.setColor(QPalette::Base, QColor(item_color));
    QStyledItemDelegate::paint(painter, s, index);
}
