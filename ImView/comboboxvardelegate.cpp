#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>

#include "comboboxvardelegate.h"
#include "kalibr.h"

ComboBoxVarDelegate::ComboBoxVarDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    kalibr = (Kalibr*)parent;
}

ComboBoxVarDelegate::~ComboBoxVarDelegate()
{

}

QWidget* ComboBoxVarDelegate::createEditor(QWidget* parent,
                                           const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    if(index.column() == 7)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "INT16(Little-endian)");
        editor->insertItem(1, "WORD16(Little-endian)");
        editor->insertItem(2, "LONGINT32(Little-endian)");
        editor->insertItem(3, "DWORD32(Little-endian)");
        editor->insertItem(4, "FLOAT32(Little-endian)");
        editor->insertItem(5, "INT16(Big-endian)");
        editor->insertItem(6, "WORD16(Big-endian)");
        editor->insertItem(7, "LONGINT32(Big-endian)");
        editor->insertItem(8, "DWORD32(Big-endian)");
        editor->insertItem(9, "FLOAT32(Big-endian)");
        editor->insertItem(10, "LONGINT32(Middle-endian)");
        editor->insertItem(11, "DWORD32(Middle-endian)");
        editor->insertItem(12, "FLOAT32(Middle-endian)");

        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxVarDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 7)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "INT16(Little-endian)")
            comboBox->setCurrentIndex(0);
        else if(value == "WORD16(Little-endian)")
            comboBox->setCurrentIndex(1);
        else if(value == "LONGINT32(Little-endian)")
            comboBox->setCurrentIndex(2);
        else if(value == "DWORD32(Little-endian)")
            comboBox->setCurrentIndex(3);
        else if(value == "FLOAT32(Little-endian)")
            comboBox->setCurrentIndex(4);
        else if(value == "INT16(Big-endian)")
            comboBox->setCurrentIndex(5);
        else if(value == "WORD16(Big-endian)")
            comboBox->setCurrentIndex(6);
        else if(value == "LONGINT32(Big-endian)")
            comboBox->setCurrentIndex(7);
        else if(value == "DWORD32(Big-endian)")
            comboBox->setCurrentIndex(8);
        else if(value == "FLOAT32(Big-endian)")
            comboBox->setCurrentIndex(9);
        else if(value == "LONGINT32(Middle-endian)")
            comboBox->setCurrentIndex(10);
        else if(value == "DWORD32(Middle-endian)")
            comboBox->setCurrentIndex(11);
        else if(value == "FLOAT32(Middle-endian)")
            comboBox->setCurrentIndex(12);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxVarDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                       const QModelIndex& index) const
{
    if(index.column() == 7)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxVarDelegate::updateEditorGeometry(QWidget* editor,
                                               const QStyleOptionViewItem& option, const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}



void ComboBoxVarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 7)
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
    }
    QStyledItemDelegate::paint(painter, option, index);
}


