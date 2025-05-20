#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include "qstyleditemdelegate.h"

class DoubleDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DoubleDelegate(QObject *parent = nullptr);
    ~DoubleDelegate() override;

    virtual QString displayText(const QVariant &value,
                                const QLocale &locale) const override;
    QString textFromValue(double value) const;
};

#endif // DOUBLEDELEGATE_H
