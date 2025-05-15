#include "comboboxdelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>

#include "kalibr.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    kalibr = (Kalibr*)parent;
}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    if(index.column() == 4)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "RTU");
        editor->insertItem(1, "ASCII");
        editor->insertItem(2, "ОВЕН");
        editor->insertItem(3, "Токовый вход 1");
        editor->insertItem(4, "Токовый вход 2");
        editor->insertItem(5, "Токовый вход 3");
        editor->insertItem(6, "Токовый вход 4");
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 4)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "RTU")
            comboBox->setCurrentIndex(0);
        else if(value == "ASCII")
            comboBox->setCurrentIndex(1);
        else if(value == "ОВЕН")
            comboBox->setCurrentIndex(2);
        else if(value == "Токовый вход 1")
            comboBox->setCurrentIndex(3);
        else if(value == "Токовый вход 2")
            comboBox->setCurrentIndex(4);
        else if(value == "Токовый вход 3")
            comboBox->setCurrentIndex(5);
        else if(value == "Токовый вход 4")
            comboBox->setCurrentIndex(6);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);

    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                    const QModelIndex& index) const
{
    if(index.column() == 4)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget* editor,
                                            const QStyleOptionViewItem& option, const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 4)
    {
        if (kalibr->deleteRows.contains(index.row()))
        {
            QColor background = kalibr->deleteRowBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
            painter->fillRect(option.rect, background);
        }
        else if (kalibr->changedRows.contains(index.row()))
        {
            QColor background = kalibr->changedColumnBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
            painter->fillRect(option.rect, background);
        }
        else if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
        {
            QColor background = kalibr->disabledCellBackgroundColor; // RGB value: https://www.rapidtables.com/web/color/blue-color.html
            painter->fillRect(option.rect, background);
        }
    }
    QStyledItemDelegate::paint(painter, option, index);
}

