#include "branchdrawingdelegate.h"
#include "qpainter.h"
#include <QStandardItemModel>
#include <QSet>



BranchDrawingDelegate::BranchDrawingDelegate(QTreeView *view, QObject *parent) :QStyledItemDelegate(parent), m_view(view)
{

}

void BranchDrawingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    // Вызов стандартной отрисовки текста и иконок
    QStyledItemDelegate::paint(painter, option, index);

    // Получаем модель и текущий индекс
    const QAbstractItemModel *model = index.model();

    // Проверяем, есть ли у узла родители (чтобы рисовать ветви)
    QModelIndex parentIndex = index.parent();

    if (!parentIndex.isValid())
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
        QPoint endPointParent(currentX, rect.top() - 10); // чуть выше

        painter->drawLine(startPoint, endPointParent);
        painter->restore();
    }

    // Получаем координаты для рисования линий
    QRect rect = option.rect;
    int centerX = rect.left() - 10; // чуть левее текста для линии

    painter->save();
    painter->setPen(QPen(Qt::black, 1));

    // Рисуем линию вверх к родительскому узлу
    QPoint startPoint(centerX, rect.top() + rect.height() / 2);
    QPoint endPointParent(centerX, rect.top() - 10); // чуть выше

    painter->drawLine(startPoint, endPointParent);

    // Рисуем линию вправо к текущему узлу (если нужно)
    QPoint startRight(centerX, rect.top() + rect.height() / 2);
    QPoint endRight(rect.left(), rect.top() + rect.height() / 2);
    painter->drawLine(startRight, endRight);

    painter->restore();
}









