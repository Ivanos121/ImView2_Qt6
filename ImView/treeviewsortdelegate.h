#ifndef TREEVIEWSORTDELEGATE_H
#define TREEVIEWSORTDELEGATE_H

#include "qsortfilterproxymodel.h"


class TreeviewSortDelegate: public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TreeviewSortDelegate(QObject *parent = nullptr);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;
};

#endif // TREEVIEWSORTDELEGATE_H
