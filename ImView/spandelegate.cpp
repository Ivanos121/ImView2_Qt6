#include <QPainter>
#include <QStandardItem>
#include <QTreeView>

#include "spandelegate.h"

SpanDelegate::SpanDelegate(QTreeView *view,QObject *parent): QStyledItemDelegate(parent), m_view(view)
{

}

SpanDelegate::~SpanDelegate()
{

}

bool SpanDelegate::shouldSpan(const QModelIndex &index) const
{
    // Здесь логика определения необходимости объединения
    // Например: объединять колонки 0 и 1 в первой строке
    auto model = index.model();
    QModelIndex Index_1 = model->index(0, 0, QModelIndex());
    QModelIndex Index_2 = model->index(1, 0, QModelIndex());
    QModelIndex Index_3 = model->index(2, 0, QModelIndex());
    QModelIndex Index_4 = model->index(3, 0, QModelIndex());
    QModelIndex Index_5 = model->index(4, 0, QModelIndex());
    QModelIndex Index_6 = model->index(5, 0, QModelIndex());
    QModelIndex Index_7 = model->index(6, 0, QModelIndex());
    QModelIndex Index_8 = model->index(7, 0, QModelIndex());
    QModelIndex Index_9 = model->index(8, 0, QModelIndex());
    QModelIndex Index_10 = model->index(9, 0, QModelIndex());
    QModelIndex nonRootIdx_1 = model->index(1, 0, Index_1);
    QModelIndex nonRootIdx_2 = model->index(2, 0, Index_1);

    if ((index == Index_1) || (index == Index_2) || (index == Index_3) || (index == Index_4)
        || (index == Index_5) || (index == Index_6) || (index == Index_7) || (index == Index_8)
        || (index == Index_9) || (index == Index_10) || (index == nonRootIdx_1)
        || (index == nonRootIdx_2))
    {
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
        //QModelIndex spanIndex = model->index(index.row(), index.column() + 1);
        if (index.column() + 1 < model->columnCount(index.parent()))
        {
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

        painter->setBrush(QBrush(Qt::green)); // ваш цвет заливки
        painter->setPen(Qt::NoPen);
        painter->drawRect(unionRect);
        QStyledItemDelegate::paint(painter, opt, index);
        painter->restore();

        // // Рисуем текст из первой ячейки (или объединённого)
        // QString text = index.data().toString();
        // painter->save();
        // painter->setClipRect(unionRect);
        // QRect textRect = unionRect.adjusted(4, 4, -4, -4);
        // painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        }}
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
        return false; // например
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
