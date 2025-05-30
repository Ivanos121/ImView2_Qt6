#ifndef PAINTDELEGATE_H
#define PAINTDELEGATE_H

#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QSerialPort>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>

class Kalibr;

class PaintDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit PaintDelegate(QObject *parent = nullptr);
    ~PaintDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

private:
    Kalibr* kalibr;
};

#endif // PAINTDELEGATE_H
