#ifndef VENT_IDENTF_H
#define VENT_IDENTF_H

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
    QTimer *times;

    void raschet_vent_identf();
public slots:
    void realtimeDataSlot();
public:
    Ui::Vent_identf *ui;
        QVector<QColor> dataLineColors_vent_identf;
    std::vector<double> polyfit(const std::vector<double> &x, const std::vector<double> &y, int degree);
        double computeError(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &coeffs);
    int bestDegree(const QVector<double> &Q, const QVector<double> &w);
};

#endif // VENT_IDENTF_H
