#ifndef POISK_H
#define POISK_H

#include <QWidget>

namespace Ui {
class poisk;
}

class poisk : public QWidget
{
    Q_OBJECT

public:
    explicit poisk(QWidget *parent = nullptr);
    ~poisk();

public:
    Ui::poisk *ui;
};

#endif // POISK_H
