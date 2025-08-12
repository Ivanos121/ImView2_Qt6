#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QSqlTableModel>
#include <QSpinBox>

#include "kalibr.h"
#include "paintdelegate.h"

PaintDelegate::PaintDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    kalibr = (Kalibr*)parent;
}

PaintDelegate::~PaintDelegate()
{

}

void PaintDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    if (kalibr->deleteRows.contains(index.row()))
    {
        painter->save();
        QColor background = kalibr->deleteRowBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
        painter->restore();
    }
    else if (kalibr->changedRows.contains(index.row()))
    {
        painter->save();
        QColor background = kalibr->changedColumnBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
        painter->restore();
    }
    else if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        painter->save();
        QColor background = kalibr->disabledCellBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
        painter->restore();
    }


        // Paint text
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget* PaintDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}
