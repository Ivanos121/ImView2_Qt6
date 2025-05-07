#include <QSerialPort>
#include "devicedigitosc.h"
#include "base.h"

DeviceDigitOsc::DeviceDigitOsc(QObject *parent)
    : QObject{parent}
{

}

int DeviceDigitOsc::init()
{
    serialPort = new QSerialPort();
    serialPort->setPortName(base.digitOscParams.portName);

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        emit digitOscFailure();
        return 1;
    }

    serialPort->setBaudRate(base.digitOscParams.speed);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    serialPort->write("s");

    return 0;
}

void DeviceDigitOsc::readData()
{
    QByteArray block;
    size_t bytes_left = 6400*7*2;
    do
    {
        serialPort->waitForReadyRead(100);
        QByteArray subblock = serialPort->read(bytes_left);
        block.append(subblock);
        bytes_left -= subblock.size();
        //printf("readed subblock %d bytes\n", subblock.size());
    } while (block.size() < 6400*7*2);

    memcpy(buf,block.data(),6400*7*2);
}

void DeviceDigitOsc::stop()
{
    serialPort->write("b");
    serialPort->flush();
    serialPort->waitForBytesWritten(100);
    serialPort->close();
    delete serialPort;
}
