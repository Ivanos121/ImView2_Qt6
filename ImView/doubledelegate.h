#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include "qstyleditemdelegate.h"

class DoubleDelegate : public QStyledItemDelegate
{    

public:
    DoubleDelegate(QObject *parent = nullptr);    
    virtual QString displayText(const QVariant &value, const QLocale &locale) const;
    QString textFromValue(double value) const;
};

#endif // DOUBLEDELEGATE_H
