#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QSerialPort>
#include <QSqlTableModel>
#include <QAbstractTableModel>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>

class Kalibr;

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);
    ~CheckBoxDelegate() override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,const QModelIndex &index) override;

private:
    Kalibr *kalibr;
};

#endif // CHECKBOXDELEGATE_H
