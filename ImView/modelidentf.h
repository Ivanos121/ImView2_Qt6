#ifndef MODELIDENTF_H
#define MODELIDENTF_H

#include <QTimer>

class ModelIdentf : public QObject
{
    Q_OBJECT
public:
    ModelIdentf();

    double Ualpha, Ubeta, Ialpha, Ibeta, psi2a,psi2b,omega,sigma,alpha, beta, kk, Ts, t, M, Mc,w;
    double Ua_prev, Ub_prev, omega_prev, psi2a_prev, psi2b_prev, Ia_prev, Ib_prev;
    double R1, L2, Lm, J, pn;    
    double Mc_n;

    void init(double _R1, double _R2, double _L1, double _L2, double _Lm);
    void rasch();    
    void stop();
};

#endif // MODELIDENTF_H
