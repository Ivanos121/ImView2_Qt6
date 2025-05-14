#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

#define BUF_SIZE 6400

class Device : public QObject
{
    Q_OBJECT
public:
    Device();
    int init();
    void readData();
    void stop();    
    uint16_t buf[BUF_SIZE][6];

signals:
    void bvasFailure();
};

#endif // DEVICE_H
