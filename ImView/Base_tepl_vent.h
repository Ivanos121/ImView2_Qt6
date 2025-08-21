#ifndef BASE_TEPL_VENT_H
#define BASE_TEPL_VENT_H

#include <QString>
#include <QVector>

struct TeplParam
{
    double y_21;
    double y_22;
    double y_01;



};
struct VentParam
{
    QString name;
    double d1p;
    double d2p;
    double b;
    double n;
    double ro;
    double sotv;
    double s0;
    double s1;
    double a1;
    double s2;
    double a2;
    double s3;
    double s4;
    double fi;
    double fi2;
    double H0;
    double Qmax;
    double Z0;
    double Z1;
    double Z2;
    double Z3;
    double Z4;
    double Z5;
    double Z6;
    double Qp;
    double Hp;
    double Vcp;
    double Pvent;
    double epsilon1;
    double epsilon2;
    double epsilon3;
    double epsilon4;
    double epsilon5;
    double epsilon6;
    double cosf;
    double K;
    double nu2;
    double v;
    QString ventIdentfFileName;
    QVector<double> w_Q_inv_koeffss;
    QVector<double> Q_H1_koeffss;
    QVector<double> Q_H2_koeffss;
    QVector<double> Q_Pv_koeffss;
};

extern TeplParam teplparam;
extern VentParam ventparam;

#endif // BASE_TEPL_VENT_H
