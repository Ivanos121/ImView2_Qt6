#include "zerocorrector.h"

double ZeroCorrector::apply(double z, double K, double K1, double K2, double K3, double Ts)
{
    double z_int = 1.0/2.0*(2*z_int_prev + (z - y_prev)*K*Ts + (z_prev - y_prev)*K*Ts);
    double u = (1.0/(2+K*Ts)) * (u_prev * (2-K1*K*Ts)+z_int*K*Ts+z_int_prev*K*Ts);
    double y = 1.0/2.0*(2*y_prev + 2*u*K3 - 2*u_prev*K3 + u*K2*K*Ts + u_prev*K2*K*Ts);
    u_prev = u;
    y_prev = y;
    z_prev = z;
    z_int_prev = z_int;
    return z - y;
}
