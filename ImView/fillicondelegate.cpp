#include "fillicondelegate.h"
#include <QPainter>
#include <QTreeView>
#include <QStandardItemModel>
#include <QApplication>

FillIconDelegate::FillIconDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}
void FillIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    painter->save();

    // Получаем стандартные параметры
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // Определяем области
    QRect rect = opt.rect;

    // Область с иконкой (обычно слева)
    QRect decorationRect = QRect();
    if (opt.icon.isNull() == false) {
        decorationRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemDecoration, &opt);
        // Закрашиваем область с иконкой
        painter->fillRect(decorationRect, QColor(Qt::red)); // светло-зеленый
    }

    // Область с линиями ветвей — это обычно внутри rect, но можно выделить её отдельно
    // Например, закрасим левую часть ячейки (где могут проходить линии)
    QRect branchLineArea = rect;
    branchLineArea.setWidth(20); // например, первые 20 пикселей слева
    painter->fillRect(branchLineArea, QColor(Qt::red)); // светло-желтый

    // Теперь вызываем стандартную отрисовку для остальной части
    QStyledItemDelegate::paint(painter, opt, index);

    painter->restore();
}
