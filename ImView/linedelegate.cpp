#include "linedelegate.h"
#include "qpainter.h"

#include <QApplication>

void LineDelegate::m_paintFunc2(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Создаём копию опций для настройки
    QStyleOptionViewItem opt = option;

    // Отключаем рисование рамки по умолчанию
    opt.state &= ~QStyle::State_HasFocus;
    opt.state &= ~QStyle::State_MouseOver;

    // Проверяем, нужно ли рисовать объединённую ячейку
    if (!shouldSpan(index))
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

void LineDelegate::m_paintFunc1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // вторая логика рисования
    // Вызов стандартной отрисовки текста и иконок
    //QStyledItemDelegate::paint(painter, option, index);

    // Получаем модель и текущий индекс
    const QAbstractItemModel *model = index.model();

    // Проверяем, есть ли у узла родители (чтобы рисовать ветви)
    QModelIndex parentIndex = index.parent();

    if (parentIndex.isValid()) {
        // Если не последний среди братьев
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
    bool isSelected = option.state & QStyle::State_Selected;
    bool isSpan = shouldSpan(index);

    if (isSelected && !isSpan)
    {
        painter->save();
        //painter->setBrush(QBrush(Qt::blue));
        painter->setBrush(QBrush(QColor(61, 174, 233)));
        //#3daee9
        painter->setPen(Qt::NoPen);
        QRect rect = option.rect;
        QRect backRect(QPoint(0, rect.topLeft().y()), QPoint(rect.bottomRight().x(), rect.bottomRight().y()));
        painter->drawRect(backRect);
        painter->restore();

        painter->save();

        // Получаем стандартные параметры
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        // Определяем области
        QRect rect1 = opt.rect;

        // Область с иконкой (обычно слева)
        QRect decorationRect = QRect();
        if (opt.icon.isNull() == false) {
            decorationRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemDecoration, &opt);
            // Закрашиваем область с иконкой
            painter->fillRect(decorationRect, QColor(Qt::red)); // светло-зеленый
        }

        // Область с линиями ветвей — это обычно внутри rect, но можно выделить её отдельно
        // Например, закрасим левую часть ячейки (где могут проходить линии)
        QRect branchLineArea = rect1;
        branchLineArea.setWidth(20); // например, первые 20 пикселей слева
        painter->fillRect(branchLineArea, QColor(Qt::red)); // светло-желтый

        // Теперь вызываем стандартную отрисовку для остальной части
       // QStyledItemDelegate::paint(painter, opt, index);

        painter->restore();
    }

    m_paintFunc2(painter, option, index);
    m_paintFunc1(painter, option, index);
    //m_paintFunc3(painter, option, index);
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
