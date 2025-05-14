#ifndef DEVICEDIGITOSC_H
#define DEVICEDIGITOSC_H

#include <QSerialPort>
#include <QObject>

#define BUF_SIZE 6400

class DeviceDigitOsc : public QObject
{
    Q_OBJECT

public:
    explicit DeviceDigitOsc(QObject *parent = nullptr);
    int init();
    void readData();
    void stop();    
    uint16_t buf[BUF_SIZE][7];

private:
    QSerialPort *serialPort;

signals:
    void digitOscFailure();

};

#endif // DEVICEDIGITOSC_H
