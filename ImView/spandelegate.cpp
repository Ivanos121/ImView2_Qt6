#include <QPainter>
#include <QTreeView>

#include "spandelegate.h"

SpanDelegate::SpanDelegate(QTreeView *view,QObject *parent): QStyledItemDelegate(parent), m_view(view)
{

}

bool SpanDelegate::shouldSpan(const QModelIndex &index) const
{
    // Здесь логика определения необходимости объединения
    // Например: объединять колонки 0 и 1 в первой строке
    if (index.column() == 0 && index.row() == 1) {
        return true;
    }
    return false;
}

void SpanDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto model = index.model();

    // Проверяем, нужно ли рисовать объединённую ячейку
    if (shouldSpan(index)) {
        // Получаем индекс следующей колонки для объединения
        QModelIndex spanIndex = model->index(index.row(), index.column() + 1);
        //QModelIndex spanIndex = index.sibling(index.row() == 0, index.column() + 1);
        QRect rect2 = m_view->visualRect(spanIndex);

        // Получаем геометрию обеих ячеек
        QRect rect1 = option.rect;
        //QRect rect2 = view->visualRect(spanIndex);

        // Объединяем области
        QRect unionRect = rect1.united(rect2);

        // Рисуем фон
        painter->save();
        painter->setClipRect(unionRect);
        QStyleOptionViewItem opt = option;
        opt.rect = unionRect;
        QStyledItemDelegate::paint(painter, opt, index);
        painter->restore();

        // Рисуем текст из первой ячейки (или объединённого)
        //QString text = index.data().toString();
        //painter->drawText(unionRect.adjusted(4, 4, -4, -4), Qt::AlignLeft | Qt::AlignVCenter, text);
    } else {
        // Обычное рисование
        QStyledItemDelegate::paint(painter, option, index);
    }
}



