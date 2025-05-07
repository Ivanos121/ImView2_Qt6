#include <QMessageBox>

#include "datasourcebvas.h"
#include "bvasthread.h"

DataSourceBVAS::DataSourceBVAS()
{
    bvasThread = new BVASThread();
    bvasDevice = new Device();
    bvasThread->setDevice(bvasDevice);

    connect(bvasThread, &BVASThread::dataReady, this, &DataSourceBVAS::read);
    connect(bvasDevice, &Device::bvasFailure, this, &DataSourceBVAS::bvasFailureSlot);

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

void DataSourceBVAS::init()
{
    bvasThread->start();
}

void DataSourceBVAS::read()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        Ua[i] = (bvasDevice->buf[i][0] - UaZeroLevel) * UaCalibrationCoeff;
        Ub[i] = (bvasDevice->buf[i][1] - UbZeroLevel) * UbCalibrationCoeff;
        Uc[i] = (bvasDevice->buf[i][2] - UcZeroLevel) * UcCalibrationCoeff;

        Ia[i] = (bvasDevice->buf[i][3] - IaZeroLevel) * IaCalibrationCoeff;
        Ib[i] = (bvasDevice->buf[i][4] - IbZeroLevel) * IbCalibrationCoeff;
        Ic[i] = (bvasDevice->buf[i][5] - IcZeroLevel) * IcCalibrationCoeff;
    }

    emit ready();
}

void DataSourceBVAS::bvasFailureSlot()
{
    stop();
    emit failure();
}

void DataSourceBVAS::stop()
{
    bvasThread->stopWorking();
    bvasThread->wait();
}
