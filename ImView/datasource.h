#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>

class DataSource : public QObject
{
    Q_OBJECT
public:
    DataSource();

    virtual double* getUa() {return nullptr;}
    virtual double* getUb() {return nullptr;}
    virtual double* getUc() {return nullptr;}
    virtual double* getIa() {return nullptr;}
    virtual double* getIb() {return nullptr;}
    virtual double* getIc() {return nullptr;}
    virtual double* getW() {return nullptr;}
    virtual double* getTime() {return nullptr;}

    virtual double getUaZeroLevel() {return 0.0;}
    virtual double getUbZeroLevel() {return 0.0;}
    virtual double getUcZeroLevel() {return 0.0;}

    virtual double getIaZeroLevel() {return 0.0;}
    virtual double getIbZeroLevel() {return 0.0;}
    virtual double getIcZeroLevel() {return 0.0;}

    virtual double getUaCalibrationCoeff() {return 0.0;}
    virtual double getUbCalibrationCoeff() {return 0.0;}
    virtual double getUcCalibrationCoeff() {return 0.0;}

    virtual double getIaCalibrationCoeff() {return 0.0;}
    virtual double getIbCalibrationCoeff() {return 0.0;}
    virtual double getIcCalibrationCoeff() {return 0.0;}

    virtual void setUaZeroLevel(double) {}
    virtual void setUbZeroLevel(double) {}
    virtual void setUcZeroLevel(double) {}

    virtual void setIaZeroLevel(double) {}
    virtual void setIbZeroLevel(double) {}
    virtual void setIcZeroLevel(double) {}

    virtual void setUaCalibrationCoeff(double) {}
    virtual void setUbCalibrationCoeff(double) {}
    virtual void setUcCalibrationCoeff(double) {}

    virtual void setIaCalibrationCoeff(double) {}
    virtual void setIbCalibrationCoeff(double) {}
    virtual void setIcCalibrationCoeff(double) {}

    virtual void init() {};
    virtual void stop() {};

signals:
    void ready();
    void failure();
};

#endif // DATASOURCE_H
