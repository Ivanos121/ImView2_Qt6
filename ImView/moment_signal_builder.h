#ifndef MOMENT_SIGNAL_BUILDER_H
#define MOMENT_SIGNAL_BUILDER_H

#include <QChart>
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
    Ui::Moment_signal_builder *ui;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    void restoreAxes();
};

#endif // MOMENT_SIGNAL_BUILDER_H
