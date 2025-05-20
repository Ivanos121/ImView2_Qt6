#ifndef COMBOBOXERRORARCHIVEDELEGATE_H
#define COMBOBOXERRORARCHIVEDELEGATE_H

#include <QString>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
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

class MainWindow;
class Kalibr;

class ComboBoxErrorArchiveDelegate : public QStyledItemDelegate
{
   Q_OBJECT

public:
    explicit ComboBoxErrorArchiveDelegate(QObject *parent = nullptr);
    ~ComboBoxErrorArchiveDelegate() override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    void changedComboBox(int /*index*/);

private:
    Kalibr *kalibr;
};

#endif // COMBOBOXERRORARCHIVEDELEGATE_H
