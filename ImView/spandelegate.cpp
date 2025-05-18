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
    if (index.column() == 0 && index.row() == 0)
    {
        return true;
    }
    return false;   
}

void SpanDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //auto model = index.model();

    // Проверяем, нужно ли рисовать объединённую ячейку
    if (shouldSpan(index)) {
        // Получаем индекс следующей колонки для объединения
        //QModelIndex spanIndex = model->index(index.row(), index.column() + 1);
        QModelIndex spanIndex = index.sibling(index.row(), index.column() + 1);
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
        QString text = index.data().toString();
        painter->save();
        painter->setClipRect(unionRect);
        QRect textRect = unionRect.adjusted(4, 4, -4, -4);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
    else
    {
        // Для остальных — рисуем как обычно
        // Но чтобы избежать двойного текста при объединении,
        // рисуем только если это "ведущая" ячейка
        if (!isPartOfSpan(index))
        {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
}

bool SpanDelegate::isPartOfSpan(const QModelIndex &index) const
{
    // Проверка: если индекс входит в объединённую область,
    // то он не должен рисовать свой текст.
    // Реализуйте по вашей логике.
    if (index.row() == 0 && index.column() == 0)
    {
        return true; // например
    }
    return false;
}

QSize SpanDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if (shouldSpan(index)) {
        // Можно увеличить размер по ширине
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setWidth(size.width() * 2); // например, удвоить ширину
        return size;
    }
    return QStyledItemDelegate::sizeHint(option, index);
}
