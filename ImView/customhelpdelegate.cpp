#include "customhelpdelegate.h"
#include "qabstractitemview.h"
#include <QHelpEvent>
#include <QToolTip>


CustomHelpDelegate::CustomHelpDelegate(QObject *parent) :QStyledItemDelegate(parent)
{

}
bool CustomHelpDelegate::helpEvent( QHelpEvent* e, QAbstractItemView* view,
                                   const QStyleOptionViewItem& option, const QModelIndex& index )
{
    if (!e || !view)
        return false;
    if (e->type() == QEvent::ToolTip)
    {
        QVariant tooltip = index.data(Qt::DisplayRole);
        if (tooltip.canConvert<QString>())
        {
            QString src=tooltip.toString();
            QToolTip::showText( e->globalPos(), QString("<div>%1</div>").arg(src.toHtmlEscaped()), view);
            return true;
        }
        if (!QStyledItemDelegate::helpEvent( e, view, option, index))
            QToolTip::hideText();
        return true;
    }

    return QStyledItemDelegate::helpEvent( e, view, option, index);
}
