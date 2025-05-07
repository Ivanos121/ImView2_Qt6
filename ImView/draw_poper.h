#ifndef DRAW_POPER_NEW_H
#define DRAW_POPER_NEW_H

#include <QWidget>

namespace Ui {
class draw_poper;
}

class draw_poper : public QWidget
{
    Q_OBJECT

public:
    explicit draw_poper(QWidget *parent = nullptr);
    ~draw_poper();

public:
    Ui::draw_poper *ui;
};

#endif // DRAW_POPER_NEW_H
