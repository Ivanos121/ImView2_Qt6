#ifndef VENT_MODEL_H
#define VENT_MODEL_H

#include <QWidget>
#include "mainwindow.h"


namespace Ui {
class vent_model;
}

class vent_model : public QWidget
{
    Q_OBJECT

public:
    explicit vent_model(QWidget *parent = nullptr);
    ~vent_model();
    MainWindow *wf;


public:
    Ui::vent_model *ui;
};

#endif // VENT_MODEL_H
