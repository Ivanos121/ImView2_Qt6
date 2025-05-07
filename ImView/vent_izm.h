#ifndef VENT_IZM_H
#define VENT_IZM_H

#include <QWidget>

namespace Ui {
class vent_izm;
}

class vent_izm : public QWidget
{
    Q_OBJECT

public:
    explicit vent_izm(QWidget *parent = nullptr);
    ~vent_izm();

public:
    Ui::vent_izm *ui;
};

#endif // VENT_IZM_H
