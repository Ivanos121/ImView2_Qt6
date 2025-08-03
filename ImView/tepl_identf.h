#ifndef TEPL_IDENTF_H
#define TEPL_IDENTF_H

#include "qelapsedtimer.h"
#include <QWidget>

class MainWindow;

namespace Ui {
class Tepl_identf;
}

class Tepl_identf : public QWidget
{
    Q_OBJECT

public:
    explicit Tepl_identf(QWidget *parent = nullptr);
    ~Tepl_identf();
    MainWindow *wf;
    QElapsedTimer *time;

    void raschet_tepl_identf();
public slots:
    void realtimeDataSlot();
private:
    Ui::Tepl_identf *ui;
};

#endif // TEPL_IDENTF_H
