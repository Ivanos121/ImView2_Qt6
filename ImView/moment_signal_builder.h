#ifndef MOMENT_SIGNAL_BUILDER_H
#define MOMENT_SIGNAL_BUILDER_H

#include "create_moment_signal_builder.h"

#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

namespace Ui {
class Moment_signal_builder;
}

class Moment_signal_builder : public QWidget
{
    Q_OBJECT

public:
    explicit Moment_signal_builder(QWidget *parent = nullptr);
    ~Moment_signal_builder();
    Ui::Moment_signal_builder *ui;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    void saveDataXml();
    void loadDataXml();
    void updateAxes();

protected slots:
    void applybutton();
    void closebutton();
    bool savePointsToXml(const QString &fileName);
    bool loadPointsFromXml(const QString &fileName);
    void add_time_value_pushButton();
    void clear_pushButton();

private:
    void updateChart();
    QChart *chart;
    QString fileName;
    Create_moment_signal_builder moment_signal_builder;
};

#endif // MOMENT_SIGNAL_BUILDER_H
