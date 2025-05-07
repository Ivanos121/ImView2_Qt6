#ifndef ALIGN_H
#define ALIGN_H

#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QtSerialPort>
#include "QtSql"
#include "QSqlDatabase"
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlTableModel>
#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>

class Align: public QSqlTableModel
{
public:
    Align(QObject *parent);
protected:
    virtual QVariant data(const QModelIndex& index, int role) const;
};

#endif // ALIGN_H
