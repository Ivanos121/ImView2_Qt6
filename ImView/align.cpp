#include "align.h"
#include <QFlags>


Align::Align(QObject *parent) : QSqlTableModel(parent)
{

}

QVariant Align::data(const QModelIndex &item, int role) const
{
    if(role==Qt::TextAlignmentRole)
    {
    if(item.column()==5)
    return int(Qt::AlignCenter);
    if(item.column()==6)
    return int(Qt::AlignCenter);
    }
    return QSqlTableModel::data(item,role);

}

