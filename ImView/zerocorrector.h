#ifndef ZEROCORRECTOR_H
#define ZEROCORRECTOR_H

class ZeroCorrector
{
public:
    double u_prev=0, z_prev=0, z_int_prev=0, y_prev=0;
    double apply(double z, double K, double K1, double K2, double K3, double Ts);
};

#endif // ZEROCORRECTOR_H
