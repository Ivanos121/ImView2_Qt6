#ifndef VENT_IDENTF_H
#define VENT_IDENTF_H

#include "qsqltablemodel.h"
#include <QWidget>

class MainWindow;

namespace Ui {
class Vent_identf;
}

class Vent_identf : public QWidget
{
    Q_OBJECT

public:
    explicit Vent_identf(QWidget *parent = nullptr);
    ~Vent_identf();
    MainWindow *wf;

    void raschet_vent_identf();
    void setDefaultVentModel();

public:
    Ui::Vent_identf *ui;
    QVector<QColor> dataLineColors_vent_identf;
    QVector<double> approximate(const QVector<double>& x,
                                const QVector<double>& y,
                                size_t degree);
    double computeError(const QVector<double> &x, const QVector<double> &y, const QVector<double> &coeffs);
    int bestDegree(const QVector<double> &x, const QVector<double> &y);

    //void on_tabWidget_currentChanged();
    void save_vent_identf();
    void one_vent();
    void two_vent();
private:
    bool isFinished;
};

#endif // VENT_IDENTF_H
