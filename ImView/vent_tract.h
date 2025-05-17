#ifndef VENT_TRACT_H
#define VENT_TRACT_H

#include <QWidget>

namespace Ui {
class Vent_tract;
}

class Vent_tract : public QWidget
{
    Q_OBJECT

public:
    explicit Vent_tract(QWidget *parent = nullptr);
    ~Vent_tract();

public:
    Ui::Vent_tract *ui;
    void onspeed(int value);
    void onmoment(int value);
    double speed;
    double moment;
};

#endif // VENT_TRACT_H
