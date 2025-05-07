#ifndef GYBRID_TEPL_MODEL_H
#define GYBRID_TEPL_MODEL_H

#include <QWidget>

namespace Ui {
class Gybrid_tepl_model;
}

class Gybrid_tepl_model : public QWidget
{
    Q_OBJECT

public:
    explicit Gybrid_tepl_model(QWidget *parent = nullptr);
    ~Gybrid_tepl_model();

private:
    Ui::Gybrid_tepl_model *ui;
};

#endif // GYBRID_TEPL_MODEL_H
