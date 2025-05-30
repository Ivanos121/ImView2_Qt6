#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QMap>

#include "qnamespace.h"
#include "qvariant.h"

class MySortFilterProxyModel: public QSortFilterProxyModel
{
    Q_OBJECT

    QMap<int,Qt::Alignment> alignMap;
    QMap<int,Qt::ItemFlags> flagMap;

public:
    explicit MySortFilterProxyModel(QObject *parent = nullptr);
    ~MySortFilterProxyModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;    
    void setAlignment(unsigned int, Qt::Alignment);
    void setAlignmentToAll(Qt::Alignment);
    void clearAlignment();    
    void setFlag(unsigned int, Qt::ItemFlags);
    void setFlagToAll(Qt::ItemFlags);
    void clearFlag();    
    void setEnabled(unsigned int index, bool FLAG);
    void setEditable(unsigned int index, bool FLAG);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // MYSORTFILTERPROXYMODEL_H
