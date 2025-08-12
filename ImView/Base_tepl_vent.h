#ifndef BASE_TEPL_VENT_H
#define BASE_TEPL_VENT_H

#include <QString>

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
};

extern TeplParam teplparam;
extern VentParam ventparam;

#endif // BASE_TEPL_VENT_H
