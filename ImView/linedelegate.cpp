#include "linedelegate.h"
#include "qpainter.h"

#include <QApplication>

void LineDelegate::m_paintFunc2(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
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
            painter->restore();

            // Рисуем текст по центру объединенной области
            //QString text = index.data(Qt::DisplayRole).toString();
            // QString text = "Объединённая ячейка";
            // QTextOption textOption(Qt::AlignCenter);

            // // Устанавливаем жирный шрифт
            // QFont boldFont = painter->font();
            // boldFont.setBold(true);
            // painter->setFont(boldFont);

            // painter->setPen(Qt::black);
            // painter->drawText(unionRect, text, textOption);

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

            QString text;
            if(index == Index_1)
            {
                text = "Основные настройки сесии";
            }

            if(index == Index_2)
            {
                text = "Идентификация параметров схемы замещения";
            }

            if(index == Index_3)
            {
                text = "Тепловая идентификация";
            }

            if(index == Index_4)
            {
                text = "Вентиляционная идентификация";
            }

            if(index == Index_5)
            {
                text = "Электромагнитная модель";
            }

            if(index == Index_6)
            {
                text = "Тепловая модель";
            }

            if(index == Index_7)
            {
                text = "Вентиляционная модель";
            }

            if(index == Index_8)
            {
                text = "Прогнозирование температур";
            }

            if(index == Index_9)
            {
                text = "Оценка остаточного теплового ресурса";
            }

            if(index == Index_10)
            {
                text = "Выходные данные";
            }

            if(index == nonRootIdx_1)
            {
                text = "Тип эксперимента";
            }

            if(index == nonRootIdx_2)
            {
                text = "Сохранение данных";
            }

            painter->save();
            QTextOption textOption(Qt::AlignCenter);

            QFont boldFont = painter->font();
            boldFont.setBold(true);
            painter->setFont(boldFont);

            painter->setPen(Qt::black);
            painter->drawText(unionRect, text, textOption);
            painter->restore();

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
}

void LineDelegate::m_paintFunc3(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Создаем копию опций для настройки
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    QRect iconRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemDecoration, &opt,nullptr);

    // Задаем цвет заливки
    QColor fillColor = Qt::green; // замените на нужный цвет

    // Рисуем заливку под иконкой
    painter->save();
    painter->setBrush(fillColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(iconRect);
    painter->restore();

    // Рисуем стандартную ячейку
    QStyledItemDelegate::paint(painter, opt, index);
}

void LineDelegate::m_paintFunc4(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    //QStyledItemDelegate::paint(painter, option, index);

    painter->save();
    QPen pen((QColor(Qt::lightGray)));
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);

    QModelIndex spanIndex = index.sibling(index.row(), index.column() + 1);
    QRect rect2 = m_view->visualRect(spanIndex);

    QRect rect1 = option.rect;
    QRect unionRect = rect1.united(rect2);

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
        QRect rect = option.rect;
        painter->drawLine(QPoint(0, rect.bottomLeft().y()), QPoint(0, rect.topLeft().y()));
        painter->drawLine(QPoint(0, rect.bottomLeft().y()), unionRect.bottomRight());
        painter->drawLine(unionRect.topRight(), unionRect.bottomRight());
    }
    else
    {
        int columnCount = index.model()->columnCount();
        QRect rect = option.rect;

        if (index.row() == index.model()->rowCount() - 1)
        {
            painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        }
        if (index.column() == columnCount - 1)
        {
            painter->drawLine(rect.topRight(), rect.bottomRight());
        }

        painter->drawLine(QPoint(0, rect.bottomLeft().y()), QPoint(0, rect.topLeft().y()));
        painter->drawLine(rect.topRight(), rect.bottomRight());
        painter->drawLine(QPoint(0, rect.bottomLeft().y()), unionRect.bottomRight());
        painter->drawLine(unionRect.topRight(), unionRect.bottomRight());
    }
    painter->restore();
}

void LineDelegate::m_paintFunc1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // вторая логика рисования
    // Вызов стандартной отрисовки текста и иконок
    //QStyledItemDelegate::paint(painter, option, index);

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
}

LineDelegate::LineDelegate(QTreeView *view, QObject *parent) :QStyledItemDelegate(parent),m_view(view)
{

}

void LineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    m_paintFunc2(painter, option, index);
    m_paintFunc1(painter, option, index);
    //m_paintFunc3(painter, option, index);

    m_paintFunc4(painter, option, index);
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
    if (index.column() == 1)
    {
        return true; // например
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
