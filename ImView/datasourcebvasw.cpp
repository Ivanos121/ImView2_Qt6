#include "datasourcebvasw.h"
#include "bvasthread.h"

DataSourceBVASw::DataSourceBVASw()
{
    bvasThread = new BVASThread();
    bvasDevice = new Device();
    bvasThread->setDevice(bvasDevice);

    connect(bvasThread, &BVASThread::dataReady, this, &DataSourceBVASw::read);
    connect(bvasDevice, &Device::bvasFailure, this, &DataSourceBVASw::bvasFailureSlot);

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

    QString serialPortName = "/dev/ttyACM0";
    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(QSerialPort::Baud115200);
}

void DataSourceBVASw::init()
{
    if (!serialPort.open(QIODevice::ReadWrite))
    {
        bvasFailureSlot();
    }
    else
    {
        bvasThread->start();
    }
}

void DataSourceBVASw::read()
{
    serialPort.write("s");

    QByteArray readData = serialPort.readAll();
    while (serialPort.waitForReadyRead(100))
    {
        readData.append(serialPort.readAll());
    }
    double speed = (readData[0] + (readData[1] << 8)) / 12800.0 * 157.0;

    for (int i = 0; i < BUF_SIZE; i++)
    {
        Ua[i] = (bvasDevice->buf[i][0] - UaZeroLevel) * UaCalibrationCoeff;
        Ub[i] = (bvasDevice->buf[i][1] - UbZeroLevel) * UbCalibrationCoeff;
        Uc[i] = (bvasDevice->buf[i][2] - UcZeroLevel) * UcCalibrationCoeff;

        Ia[i] = (bvasDevice->buf[i][3] - IaZeroLevel) * IaCalibrationCoeff;
        Ib[i] = (bvasDevice->buf[i][4] - IbZeroLevel) * IbCalibrationCoeff;
        Ic[i] = (bvasDevice->buf[i][5] - IcZeroLevel) * IcCalibrationCoeff;

        w[i] = speed;
    }

    emit ready();
}

void DataSourceBVASw::bvasFailureSlot()
{
    stop();
    emit failure();
}

void DataSourceBVASw::stop()
{
    serialPort.close();
    bvasThread->stopWorking();
    bvasThread->wait();
}
