#ifndef BVASTHREAD_H
#define BVASTHREAD_H

#include <QThread>

#include "device.h"

class BVASThread : public QThread
{
    Q_OBJECT

public:
    explicit BVASThread() : QThread() { }
    virtual void run();
    void stopWorking();    
    void setDevice(Device *);

protected:
    bool stopping;
    Device *bvasDevice;    
    int counter;

signals:
    void dataReady();
};

#endif // BVASTHREAD_H
