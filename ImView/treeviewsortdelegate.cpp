#include "treeviewsortdelegate.h"

TreeviewSortDelegate::TreeviewSortDelegate(QObject *parent): QSortFilterProxyModel(parent)
{

}

TreeviewSortDelegate::~TreeviewSortDelegate()
{

}


bool TreeviewSortDelegate::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
    // check the current item
    bool result = QSortFilterProxyModel::filterAcceptsRow(source_row,source_parent);
    QModelIndex currntIndex = sourceModel()->index(source_row, 0, source_parent);
    if (sourceModel()->hasChildren(currntIndex)) {
        // if it has sub items
        for (int i = 0; i < sourceModel()->rowCount(currntIndex) && !result; ++i) {
            // keep the parent if a children is shown
            result = result || filterAcceptsRow(i, currntIndex);
        }
    }
    return result;
}
