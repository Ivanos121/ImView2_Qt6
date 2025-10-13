#include "branchdrawingdelegate.h"
#include "qpainter.h"
#include <QStandardItemModel>
#include <QSet>

BranchDrawingDelegate::BranchDrawingDelegate(QTreeView *view, QObject *parent) :QStyledItemDelegate(parent), m_view(view)
{

}

int BranchDrawingDelegate::getItemLevel(const QModelIndex &index) const
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

bool BranchDrawingDelegate::isItemLast(const QModelIndex &index, int level) const
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

void BranchDrawingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    // Вызов стандартной отрисовки текста и иконок
    QStyledItemDelegate::paint(painter, option, index);

    // Получаем модель и текущий индекс
    //const QAbstractItemModel *model = index.model();

    // Проверяем, есть ли у узла родители (чтобы рисовать ветви)
    QModelIndex parentIndex = index.parent();

    if (parentIndex.isValid())
    {
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
