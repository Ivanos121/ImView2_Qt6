#ifndef TEPLOVENT_H
#define TEPLOVENT_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class teplovent;
}

class teplovent : public QWidget
{
    Q_OBJECT

public:
    explicit teplovent(QWidget *parent = nullptr);
    ~teplovent();

public:
    Ui::teplovent *ui;
    MainWindow *wf;
};


#endif // TEPLOVENT_H
