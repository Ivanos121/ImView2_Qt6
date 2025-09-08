#ifndef SIGNAL_BUILDER_H
#define SIGNAL_BUILDER_H

#include "qchartview.h"
#include "qlineseries.h"
#include "qvalueaxis.h"
#include "create_signal_builder.h"
#include <QWidget>

namespace Ui {
class Signal_builder;
}

class Signal_builder : public QWidget
{
    Q_OBJECT

public:
    explicit Signal_builder(QWidget *parent = nullptr);
    ~Signal_builder();

protected slots:
    void apply_signal_builder();
    void close_signal_builder();


public:
    Ui::Signal_builder *ui;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    void saveDataXml();
    void loadDataXml();
    void updateAxes();

signals:
    void dataReady(const QVector<QPointF> &points);

protected slots:
    bool savePointsToXml(const QString &fileName);
    bool loadPointsFromXml(const QString &fileName);
    void resieve_dannie();
private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonClear_clicked();

private:
    void updateChart();
    Create_signal_builder signalBuilder;
    QVector<QPointF> paintdata;
    QChart *chart;
    QString fileName;
    //Graph *graph;
};

#endif // SIGNAL_BUILDER_H
