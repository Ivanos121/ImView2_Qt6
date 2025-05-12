#ifndef MODEL_EL_H
#define MODEL_EL_H

#include <QTimer>

extern double tcpp;

class Model_el : public QObject
{
    Q_OBJECT
public:


    enum ElDriveSystems
    {
        DIRECT_START,
        VOLTAGE_REGULATION,
        FREQUENCY_REGULATION
    };

    Model_el();
    double Ualpha, Ubeta, Ialpha, Ibeta, psi2a,psi2b,omega,sigma,alpha, beta, kk, Ts, t, M, Mc,w;
    double Ua_prev, Ub_prev, omega_prev, psi2a_prev, psi2b_prev, Ia_prev, Ib_prev;
    double R1, L2, Lm, J, pn;
    double Ua, Ub, Uc, Ia, Ib, Ic;
    double p_akt_a, p_akt_b, p_akt_c, p_akt, i_dev_a, i_dev_b, i_dev_c, u_dev_a, u_dev_b, u_dev_c,
    p_poln_a, p_poln_b, p_poln_c, p_poln, p_reakt_a, p_reakt_b, p_reakt_c, p_reakt, cos_f_a,
    cos_f_b, cos_f_c, cos_f;
    double tp, Tc, Mc_n;
    QString S;
    void init_el(double _R1,
                 double _R2,
                 double _L1,
                 double _L2,
                 double _Lm,
                 QString _S,
                 double _tp,
                 double _Tc,
                 ElDriveSystems _elds);
    void rasch();

    void stop();

    QTimer timer;

private:
    ElDriveSystems elDriveSystem;

public slots:
    void timerTimeout();

signals:
    void ready();

};

#endif // MODEL_EL_H
