#ifndef DATASOURCEBVASW_H
#define DATASOURCEBVASW_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>

#include "device.h"
#include "datasource.h"

class BVASThread;

class DataSourceBVASw: public DataSource
{
    Q_OBJECT
public:
    DataSourceBVASw();
    void init();
    void stop();

    BVASThread *bvasThread;
    Device *bvasDevice;

    double* getUa() {return Ua;}
    double* getUb() {return Ub;}
    double* getUc() {return Uc;}
    double* getIa() {return Ia;}
    double* getIb() {return Ib;}
    double* getIc() {return Ic;}
    double* getW() {return w;}

    double getUaZeroLevel() {return UaZeroLevel;}
    double getUbZeroLevel() {return UbZeroLevel;}
    double getUcZeroLevel() {return UcZeroLevel;}

    double getIaZeroLevel() {return IaZeroLevel;}
    double getIbZeroLevel() {return IbZeroLevel;}
    double getIcZeroLevel() {return IcZeroLevel;}

    double getUaCalibrationCoeff() {return UaCalibrationCoeff;}
    double getUbCalibrationCoeff() {return UbCalibrationCoeff;}
    double getUcCalibrationCoeff() {return UcCalibrationCoeff;}

    double getIaCalibrationCoeff() {return IaCalibrationCoeff;}
    double getIbCalibrationCoeff() {return IbCalibrationCoeff;}
    double getIcCalibrationCoeff() {return IcCalibrationCoeff;}

    void setUaZeroLevel(double level) {UaZeroLevel = level;}
    void setUbZeroLevel(double level) {UbZeroLevel = level;}
    void setUcZeroLevel(double level) {UcZeroLevel = level;}

    void setIaZeroLevel(double level) {IaZeroLevel = level;}
    void setIbZeroLevel(double level) {IbZeroLevel = level;}
    void setIcZeroLevel(double level) {IcZeroLevel = level;}

    void setUaCalibrationCoeff(double coeff) {UaCalibrationCoeff = coeff;}
    void setUbCalibrationCoeff(double coeff) {UbCalibrationCoeff = coeff;}
    void setUcCalibrationCoeff(double coeff) {UcCalibrationCoeff = coeff;}

    void setIaCalibrationCoeff(double coeff) {IaCalibrationCoeff = coeff;}
    void setIbCalibrationCoeff(double coeff) {IbCalibrationCoeff = coeff;}
    void setIcCalibrationCoeff(double coeff) {IcCalibrationCoeff = coeff;}

private:
    double UaZeroLevel;
    double UbZeroLevel;
    double UcZeroLevel;

    double IaZeroLevel;
    double IbZeroLevel;
    double IcZeroLevel;

    double UaCalibrationCoeff;
    double UbCalibrationCoeff;
    double UcCalibrationCoeff;

    double IaCalibrationCoeff;
    double IbCalibrationCoeff;
    double IcCalibrationCoeff;

    double Ua[BUF_SIZE];
    double Ub[BUF_SIZE];
    double Uc[BUF_SIZE];

    double Ia[BUF_SIZE];
    double Ib[BUF_SIZE];
    double Ic[BUF_SIZE];
    double w[BUF_SIZE];

    QSerialPort serialPort;

public slots:
    void read();
    void bvasFailureSlot();
};

#endif // DATASOURCEBVASW_H
