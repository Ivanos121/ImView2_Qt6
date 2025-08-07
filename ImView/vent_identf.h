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
};

#endif // VENT_IDENTF_H
