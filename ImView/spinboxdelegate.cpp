#include <QSpinBox>

#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget* SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    // editor->setFrame(false);
    // editor->setMinimum(0);
    // editor->setMaximum(100);
    editor->setRange(-100.0, 100.0);
    editor->setSingleStep(0.1);
    editor->setDecimals(3);

    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    if (spinBox) {
        spinBox->setValue(value);
    }
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    if (spinBox) {
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
