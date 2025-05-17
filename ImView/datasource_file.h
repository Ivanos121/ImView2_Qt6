#ifndef DATASOURCE_FILE_H
#define DATASOURCE_FILE_H

#include <QWidget>
#include <QTimer>

#include "datasource.h"
#include "device.h"

class DataSource_file : public DataSource
{
    Q_OBJECT
public:
    DataSource_file();
    void init();
    void stop();

    QTimer *dataTimer;

    double* getUa() {return ua;};
    double* getUb() {return ub;};
    double* getUc() {return uc;};
    double* getIa() {return ia;};
    double* getIb() {return ib;};
    double* getIc() {return ic;};
    double* getW() {return w;};
    double* getTime() {return time;};

private:
    double ua[BUF_SIZE];
    double ub[BUF_SIZE];
    double uc[BUF_SIZE];
    double ia[BUF_SIZE];
    double ib[BUF_SIZE];
    double ic[BUF_SIZE];
    double w[BUF_SIZE];
    double time[BUF_SIZE];

public slots:
    void read();

};

#endif // DATASOURCE_FILE_H
