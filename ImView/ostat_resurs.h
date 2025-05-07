#ifndef OSTAT_RESURS_H
#define OSTAT_RESURS_H

#include <QWidget>

namespace Ui {
class Ostat_resurs;
}

class Ostat_resurs : public QWidget
{
    Q_OBJECT

public:
    explicit Ostat_resurs(QWidget *parent = nullptr);
    ~Ostat_resurs();

public:
    Ui::Ostat_resurs *ui;
};

#endif // OSTAT_RESURS_H
