#ifndef VENT_MODEL_H
#define VENT_MODEL_H

#include <QWidget>
#include "model_el.h"

class MainWindow;

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
    Model_el model_el;

public:
    Ui::vent_model *ui;
    void vent_model_start();
    void vent_model_stop();

public slots:
    void modelReady();
};

#endif // VENT_MODEL_H
