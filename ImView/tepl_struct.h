#ifndef TEPL_STRUCT_H
#define TEPL_STRUCT_H

#include <QString>

struct Tepl_struct
{
    double P1;
    double dPel1;
    double dPct;
    double dPel2;
    double dPmech;
    double dPdob;
    double P2;
    double kpd;
    double cosf;
    double w_0;
    double Pelm;
};
extern Tepl_struct tepl_struct;

#endif // TEPL_STRUCT_H
