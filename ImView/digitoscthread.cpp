#include "digitoscthread.h"

void DigitOscThread::run()
{
    stopping = true;
    if (deviceDigitOsc->init() == 1)
    {
        return;
    }
    counter = 0;

    while (stopping)
    {
        counter++;
        deviceDigitOsc->readData();
        //QApplication::postEvent(receiver, new QEvent(QEvent::User));
        emit dataReady();
    }
    deviceDigitOsc->stop();
}

void DigitOscThread::stopWorking()
{
    stopping = false;
}

void DigitOscThread::setDevice(DeviceDigitOsc *dev)
{
    deviceDigitOsc = dev;
}
