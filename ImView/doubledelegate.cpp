#include "doubledelegate.h"
#include "qobject.h"

#include <bits/locale_classes.h>


DoubleDelegate::DoubleDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QString DoubleDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    if (value.type() == QVariant::Double) {
        return QString().asprintf("%.6g", value.toDouble()).replace(',','.');
    }
    return QStyledItemDelegate::displayText(value, locale);
}

QString DoubleDelegate::textFromValue(double value) const
{
    QLocale().toString(value, 'f', 2);
    return QString::number(value, 'f', 2);
}
