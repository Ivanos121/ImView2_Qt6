#ifndef MODEL_H
#define MODEL_H

#include "datasource.h"

class Model
{
public:
    Model();
    void init(double P_nom, double n_nom, double U_fnom,
              double cosf_nom, double kpd_nom, double muk, double n_0, double _gd, double _gb, double _gp,
                     double _ki, double _kpsi, double _gpsi);
    void rasch(DataSource *dataSource);
    double R1,R2,L,Lm;
    QString dvig;
    const double Ts=0.0001;
    Model *model;
};

#endif // MODEL_H
