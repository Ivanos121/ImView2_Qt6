#ifndef ACTION_CREATE_H
#define ACTION_CREATE_H

#include <QDialog>

#include "mysvgwidget.h"

class MainWindow;

namespace Ui {
class Action_create;
}

class Action_create : public QDialog
{
    Q_OBJECT

public:
    explicit Action_create(QWidget *parent = nullptr);
    ~Action_create();
    Action_create *crce;
    MainWindow *wf;
    MySvgWidget *svgwidget,  *svgwidget2, *svgwidget3, *svgwidget4,
        *svgwidget5,  *svgwidget6, *svgwidget7;

protected slots:
    void Action_closes();
    void click_open_progect(const QModelIndex &idx);
private:
    Ui::Action_create *ui;
};

#endif // ACTION_CREATE_H
