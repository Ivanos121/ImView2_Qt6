#ifndef VENT_IDENTF_H
#define VENT_IDENTF_H

#include <QWidget>

namespace Ui {
class Vent_identf;
}

class Vent_identf : public QWidget
{
    Q_OBJECT

public:
    explicit Vent_identf(QWidget *parent = nullptr);
    ~Vent_identf();

private:
    Ui::Vent_identf *ui;
};

#endif // VENT_IDENTF_H
