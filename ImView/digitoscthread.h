#ifndef DIGITOSCTHREAD_H
#define DIGITOSCTHREAD_H

#include <QThread>
#include <QObject>

#include "devicedigitosc.h"

class DigitOscThread : public QThread
{
    Q_OBJECT

public:
    DigitOscThread() : QThread() { }
    virtual void run();
    void stopWorking();
    void setDevice(DeviceDigitOsc *);

protected:
    bool stopping;
    DeviceDigitOsc *deviceDigitOsc;
    int counter;

signals:
    void dataReady();
};

#endif // DIGITOSCTHREAD_H
