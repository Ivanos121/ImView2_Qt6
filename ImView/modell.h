#ifndef MODELL_H
#define MODELL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>

class Modell : public QSqlTableModel
{
public:
    explicit Modell();
    ~Modell() override;

    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value,
                         int role = Qt::EditRole) override;
    QVariant data2 ( const QModelIndex & index, int role = Qt::DisplayRole );
    void onChecked(int index, int orientation);
    void getColorForRow(const QModelIndex &row);

signals:
    //void dataChanged(const QModelIndex &, const QModelIndex &, const QVector <int> &);
};

#endif // MODELL_H
