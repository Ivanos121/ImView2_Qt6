#include "linedelegate.h"
#include "qpainter.h"

#include <QApplication>

LineDelegate::LineDelegate(QTreeView *view, QObject *parent) :QStyledItemDelegate(parent),m_view(view)
{
    m_paintFunc2 = [this](QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)
    {
        auto model = index.model();

        // Создаём копию опций для настройки
        QStyleOptionViewItem opt = option;

        // Отключаем рисование рамки по умолчанию
        opt.state &= ~QStyle::State_HasFocus;
        opt.state &= ~QStyle::State_MouseOver;


        // Проверяем, нужно ли рисовать объединённую ячейку
        if (shouldSpan(index))
        {
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

                // Рисуем текст по центру объединенной области
                //QString text = index.data(Qt::DisplayRole).toString();
                QString text = "Объединённая ячейка";
                QTextOption textOption(Qt::AlignCenter);

                // Устанавливаем жирный шрифт
                QFont boldFont = painter->font();
                boldFont.setBold(true);
                painter->setFont(boldFont);

                painter->setPen(Qt::black);
                painter->drawText(unionRect, text, textOption);

                auto model = index.model();
                QModelIndex Index_1 = model->index(0, 0, QModelIndex());

                if(index == Index_1)
                {
                // Рисуем текст по центру или слева
                 QString text = "Объединённая ячейка";
                 painter->setPen(Qt::black); // цвет текста
                 painter->drawText(unionRect, Qt::AlignVCenter | Qt::AlignVCenter, text);
                }

                QStyledItemDelegate::paint(painter, opt, index);
                if (index == index.sibling(index.row(), index.column()))
                {
                    QStyledItemDelegate::paint(painter, opt, index);
                }
                painter->restore();
            }

            else
            {
                // Последняя колонка в спане — ничего не рисуем (или рисуем как обычно)
            }
        }
        else
        {
            if (!isPartOfSpan(index))
            {
                // Просто рисуем обычную ячейку без рамки
                QStyleOptionViewItem opt2 = opt;
                opt2.state &= ~QStyle::State_HasFocus; // отключить фокусные рамки

                // Убираем границы у стиля по умолчанию:
                QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem,
                                                     &opt2, painter);

                // Или просто вызываем базовый метод:
                QStyledItemDelegate::paint(painter, opt2, index);
            }
        }
    };

    m_paintFunc1 = [this](QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)
    {
        // вторая логика рисования
        // Вызов стандартной отрисовки текста и иконок
        QStyledItemDelegate::paint(painter, option, index);

        // Получаем модель и текущий индекс
        const QAbstractItemModel *model = index.model();

        // Проверяем, есть ли у узла родители (чтобы рисовать ветви)
        QModelIndex parentIndex = index.parent();

        /*if (parentIndex.isValid())
    {
        QRect rect = option.rect;
        int currentX = rect.left() - 10; // чуть левее текста

        painter->save();
        painter->setPen(QPen(Qt::black, 1));

        // for (const QModelIndex &rootIdx : m_rootIndices) {
        //     if (rootIdx == index)
        //         continue; // не рисуем линию к самому себе


        // }
        QPoint startPoint(currentX, rect.top() + rect.height() / 2);
        QPoint endPointParent(currentX, rect.top()); // чуть выше

        painter->drawLine(startPoint, endPointParent);
        painter->restore();
    }
*/
        if (parentIndex.isValid()) {
            //int rowCount = model->rowCount(parentIndex);
            // Если не последний среди братьев
            //if (!(rowCount > 0 && index.row() == rowCount - 1)) {
            if (!isItemLast(index, 0))
            {
                // Получаем координаты для рисования линий
                QRect rect = option.rect;
                int centerX = rect.left() - 10; // чуть левее текста для линии


                painter->save();
                QPen pen((QColor(Qt::lightGray)));
                pen.setStyle(Qt::SolidLine);
                painter->setPen(pen);

                // Рисуем линию вниз к следующему узлу
                QPoint startPoint(centerX, rect.top() + rect.height() / 2);
                QPoint endPointParent(centerX, rect.bottom());

                painter->drawLine(startPoint, endPointParent);
                painter->restore();
            }

            // Получаем координаты для рисования линий
            QRect rect = option.rect;
            int centerX = rect.left() - 10; // чуть левее текста для линии

            painter->save();
            //painter->setPen(QPen(Qt::black, 1));
            QPen pen((QColor(Qt::lightGray)));
            pen.setStyle(Qt::SolidLine);
            painter->setPen(pen);
            // Рисуем линию вверх к родительскому узлу
            QPoint startPoint(centerX, rect.top() + rect.height() / 2);
            QPoint endPointParent(centerX, rect.top()); // чуть выше

            painter->drawLine(startPoint, endPointParent);

            // Рисуем линию вправо к текущему узлу (если нужно)
            QPoint startRight(centerX, rect.top() + rect.height() / 2);
            QPoint endRight(rect.left(), rect.top() + rect.height() / 2);
            painter->drawLine(startRight, endRight);

            int itemLevel = getItemLevel(index);
            int levelStep = 20;

            for (int i = 0; i < itemLevel; i++) {
                // Рисуем линию предыдущего уровня насквозь
                if (!isItemLast(index, i+1))
                {
                    QPoint startTopPrev1(centerX - (i + 1)*levelStep, rect.top());
                    QPoint startBottomPrev1(centerX - (i + 1)*levelStep, rect.bottom());
                    painter->drawLine(startTopPrev1, startBottomPrev1);
                }
            }

            painter->restore();
        }
    };
}

void LineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    // Вызов первой функции
    if (m_paintFunc1)
    {
        m_paintFunc1(painter, option, index);
    }
    // Вызов второй функции
    if (m_paintFunc2)
    {
        m_paintFunc2(painter, option, index);
    }
}

bool LineDelegate::shouldSpan(const QModelIndex &index) const
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

bool LineDelegate::isPartOfSpan(const QModelIndex &index) const
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

int LineDelegate::getItemLevel(const QModelIndex &index) const
{
    int level = 0;
    QModelIndex currentIndex = index;

    // Поднимаемся по иерархии, пока не достигнем корня
    while (currentIndex.isValid()) {
        currentIndex = currentIndex.parent();
        level++;
    }

    return level - 1; // Уменьшаем на 1, чтобы не считать корень
}

bool LineDelegate::isItemLast(const QModelIndex &index, int level) const
{
    const QAbstractItemModel *model = index.model();

    QModelIndex parentIndex = index;
    for (int i = 0; i < level; i++)
    {
        parentIndex = parentIndex.parent();
    }

    QModelIndex parentParentIndex = parentIndex.parent();
    if (parentParentIndex.isValid())
    {
        int rowCount = model->rowCount(parentParentIndex);
        if (rowCount > 0 && (parentIndex.row() == (rowCount - 1)))
        {
            return true;
        }
    }
    else
    {
        int rowCount = model->rowCount();
        if (rowCount > 0 && (parentIndex.row() == (rowCount - 1)))
        {
            return true;
        }
    }
    return false;
}

QSize LineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    if (shouldSpan(index))
    {
        int totalWidth = size.width();
        auto model = index.model();
        int colCount = model->columnCount(index.parent());
        for (int col = index.column() + 1; col < colCount; ++col)
        {
            QModelIndex siblingIndex = index.sibling(index.row(), col);
            totalWidth += QStyledItemDelegate::sizeHint(option, siblingIndex).width();
        }
        size.setWidth(totalWidth);
    }
    return size;
}
