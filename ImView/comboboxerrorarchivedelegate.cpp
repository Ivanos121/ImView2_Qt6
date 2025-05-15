#include "comboboxerrorarchivedelegate.h"

#include <QString>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>

#include "kalibr.h"

ComboBoxErrorArchiveDelegate::ComboBoxErrorArchiveDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    kalibr = (Kalibr*)parent;
}

QWidget* ComboBoxErrorArchiveDelegate::createEditor(QWidget* parent,
                                                    const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (kalibr->disabledCells.contains(QPoint(index.row(), index.column())))
    {
        return nullptr;
    }

    if(index.column() == 9)
    {
        QComboBox* editor = new QComboBox(parent);
        editor->insertItem(0, "выкл");
        editor->insertItem(1, "вкл");
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxErrorArchiveDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == 9)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(value == "выкл")
            comboBox->setCurrentIndex(0);
        else if(value == "вкл")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);

    }else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxErrorArchiveDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                                const QModelIndex& index) const
{
    if(index.column() == 9)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ComboBoxErrorArchiveDelegate::updateEditorGeometry(QWidget* editor,
                                                        const QStyleOptionViewItem& option, const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxErrorArchiveDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 9)
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

