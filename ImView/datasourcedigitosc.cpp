#include "datasourcedigitosc.h"
#include "digitoscthread.h"

DataSourceDigitOsc::DataSourceDigitOsc()
{
    digitOscThread = new DigitOscThread();
    deviceDigitOsc = new DeviceDigitOsc();
    digitOscThread->setDevice(deviceDigitOsc);

    connect(digitOscThread, &DigitOscThread::dataReady, this, &DataSourceDigitOsc::read);
    connect(deviceDigitOsc, &DeviceDigitOsc::digitOscFailure, this, &DataSourceDigitOsc::bvasFailureSlot);

    /*UaZeroLevel = 34833.125469;
    UbZeroLevel = 2091.935000;
    UcZeroLevel = 2099.24;

    IaZeroLevel = 55297.912656;
    IbZeroLevel = 22534.149688;
    IcZeroLevel = 22623.8;*/

    UaZeroLevel = 0.0;
    UbZeroLevel = 0.0;
    UcZeroLevel = 0.0;

    IaZeroLevel = 0.0;
    IbZeroLevel = 0.0;
    IcZeroLevel = 0.0;

    UaCalibrationCoeff = 1.0;
    UbCalibrationCoeff = 1.0;
    UcCalibrationCoeff = 1.0;

    IaCalibrationCoeff = 1.0;
    IbCalibrationCoeff = 1.0;
    IcCalibrationCoeff = 1.0;

}

void DataSourceDigitOsc::init()
{
    digitOscThread->start();
}

void DataSourceDigitOsc::read()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        Ua[i] = (deviceDigitOsc->buf[i][3] - UaZeroLevel) * UaCalibrationCoeff;
        Ub[i] = (deviceDigitOsc->buf[i][4] - UbZeroLevel) * UbCalibrationCoeff;
        Uc[i] = (deviceDigitOsc->buf[i][5] - UcZeroLevel) * UcCalibrationCoeff;

        Ia[i] = (deviceDigitOsc->buf[i][0] - IaZeroLevel) * IaCalibrationCoeff;
        Ib[i] = (deviceDigitOsc->buf[i][1] - IbZeroLevel) * IbCalibrationCoeff;
        Ic[i] = (deviceDigitOsc->buf[i][2] - IcZeroLevel) * IcCalibrationCoeff;

        w[i] = deviceDigitOsc->buf[i][6] / 12800.0 * 157.0;
    }

    emit ready();
}

void DataSourceDigitOsc::bvasFailureSlot()
{
    stop();
    emit failure();
}

void DataSourceDigitOsc::stop()
{
    digitOscThread->stopWorking();
    digitOscThread->wait();
}

