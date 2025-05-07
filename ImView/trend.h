#ifndef TREND_H
#define TREND_H

#include <QWidget>
#include <QGraphicsTextItem>
#include <QDomDocument>
#include <QTimer>
#include <QTimer>
#include <QElapsedTimer>
#include "plot.h"
#include "mainwindow.h"

namespace Ui {
class Trend;
}

class Trend : public QWidget
{
    Q_OBJECT

public:
    explicit Trend(QWidget *parent = nullptr);
    ~Trend();

    Ui::Trend *ui;

    MainWindow *wf;
    void startTeplo();
    void stopTeplo();
    double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11,y_12,y_13,y_14,y_15,y_16;
    Trend *trend;



private slots:
    void on_timerTimeout();
//    void setcolorincell(int row, int column);


    void edit_graf();
    void setcolorincell(int row, int column);
private:

    QDomDocument doc,doc3,doc4;
    QTimer timer;
    double t;
    QVector<QColor> dataLineColors;

    double maxY2;
    double minY2;

    double count;
    double max;



};

#endif // TREND_H
