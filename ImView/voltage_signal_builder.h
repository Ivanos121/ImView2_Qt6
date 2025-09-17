#ifndef VOLTAGE_SIGNAL_BUILDER_H
#define VOLTAGE_SIGNAL_BUILDER_H

#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

namespace Ui {
class Voltage_signal_builder;
}

class Voltage_signal_builder : public QWidget
{
    Q_OBJECT

public:
    explicit Voltage_signal_builder(QWidget *parent = nullptr);
    ~Voltage_signal_builder();

protected slots:
    void plotGraph();
    void clearGraph();
    void saveGraph();
    void loadGraph();
    bool savePointsToXml(const QString &fileName);
    bool loadPointsFromXml(const QString &fileName);
    void apply_pushButton();
    void close_pushButton();

private:
    Ui::Voltage_signal_builder *ui;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    void restoreAxes();
};

#endif // VOLTAGE_SIGNAL_BUILDER_H
