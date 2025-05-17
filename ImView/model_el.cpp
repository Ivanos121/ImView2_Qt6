#include <cmath>

#include "model_el.h"
#include "base.h"
#include "tepl_struct.h"
#include "mainwindow.h"

double tcpp;

Model_el::Model_el()
{
    connect(&timer, &QTimer::timeout, this, &Model_el::timerTimeout);    
}

void Model_el::init_el(double _R1,
                       double _R2,
                       double _L1,
                       double _L2,
                       double _Lm,
                       QString _S,
                       double _Tc,
                       double _tp,
                       ElDriveSystems _elds)
{
    elDriveSystem = _elds;

    double L1 = _L1;
    R1 = _R1;
    double R2 = _R2;
    L2 = _L2;
    Lm = _Lm;

    S = _S;
    tp = _tp;
    Tc = _Tc;

    sigma=L1-((Lm*Lm)/(L2));
    alpha=R2/L2;
    beta=Lm/(sigma*L2);
    pn=2;
    J=base.J_dv;
    t=0;
    M=0;
    Mc=0;
    kk=1;
    Ua_prev = 0.0;
    Ub_prev = 0.0;
    omega_prev = 0.0;
    psi2a_prev = 0.0;
    psi2b_prev = 0.0;
    Ia_prev = 0.0;
    Ib_prev = 0.0;

    timer.start(100);
}

void Model_el::rasch()
{
    bool circuitOn = true;

    double Ts=0.000032;
    t=t+Ts;

    double tt=t;
    tcpp =t;

    double Um = base.U_fnom;
    double w0 = Um / 220.0 * 314.0;

    double McReakt;

    //progress->setValue(t);

    if (omega >= 1.0)
    {
        McReakt = base.Mc_n;
    }
    else if ((omega > -1.0) && (omega < 1.0))
    {
        McReakt = 0.0;
    }
    else
    {
        McReakt = -base.Mc_n;
    }

    if(S == "Режим S1")
    {
        Mc = McReakt;
    }

    if(S == "Режим S2")
    {
        Mc=McReakt;
        if(tt<=tp)
        {
            circuitOn = true;
        }
        if(tt>tp)
        {
            circuitOn = false;
        }
    }

    if(S == "Режим S3")
    {
        Mc=McReakt;
        while(tt>Tc)
        {
            tt-=Tc;
        }
        if(tt<tp)
        {
            circuitOn = true;
        }
        if(tt>tp)
        {
            circuitOn = false;
        }
    }

    if(S == "Режим S6")
    {
        while(tt>Tc)
        {
            tt-=Tc;
        }
        if(tt<tp)
        {
            Mc = McReakt;
        }
        if(tt>tp)
        {
            Mc = 0;
        }
    }

    if (elDriveSystem == FREQUENCY_REGULATION)
    {
        w0 = Um / 220.0 * 314.0;
    }

    if (circuitOn)
    {
        Ualpha=Um * sqrt(2) * sin(w0*t);
        Ubeta=Um * sqrt(2) * sin(w0*t-M_PI/2.0);
        omega=omega_prev;
        Ialpha=((((4*pow(Ts,2)*beta*psi2a_prev+4*pow(Ts,2)*Ia_prev)*pow(omega,2)+4*pow(Ts,2)*beta*omega_prev*psi2a_prev*omega)*pow(kk,2)*pow(pn,2)+((((4*Lm*pow(Ts,2)*alpha*pow(beta,2)-4*pow(Ts,2)*alpha*beta)*psi2b_prev+8*Lm*pow(Ts,2)*alpha*beta*Ib_prev)*omega+(4*Lm*pow(Ts,2)*alpha*pow(beta,2)+4*pow(Ts,2)*alpha*beta)*omega_prev*psi2b_prev)*pow(kk,2)+(8*Ts*beta*psi2b_prev*omega+8*Ts*beta*omega_prev*psi2b_prev)*kk)*pn+((8*Lm*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*pow(Ts,2)*pow(alpha,2)*beta)*psi2a_prev+(4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*Ia_prev)*pow(kk,2)+(16*Ts*alpha*beta*psi2a_prev+16*Ts*alpha*Ia_prev)*kk+16*Ia_prev)*pow(sigma,2)+((2*pow(Ts,3)*pow(omega,2)*Ualpha+(2*pow(Ts,3)*Ua_prev+2*R1*pow(Ts,3)*beta*psi2a_prev)*pow(omega,2)+2*R1*pow(Ts,3)*beta*omega_prev*psi2a_prev*omega)*pow(kk,3)*pow(pn,2)+((omega*(Lm*pow(Ts,3)*alpha*beta*(2*Ubeta+2*Ub_prev)-2*R1*pow(Ts,3)*alpha*beta*psi2b_prev)+2*R1*pow(Ts,3)*alpha*beta*omega_prev*psi2b_prev)*pow(kk,3)+(4*R1*pow(Ts,2)*beta*psi2b_prev*omega+4*R1*pow(Ts,2)*beta*omega_prev*psi2b_prev)*pow(kk,2))*pn+((2*Lm*pow(Ts,3)*pow(alpha,2)*beta+2*pow(Ts,3)*pow(alpha,2))*Ualpha+(2*Lm*pow(Ts,3)*pow(alpha,2)*beta+2*pow(Ts,3)*pow(alpha,2))*Ua_prev+4*R1*pow(Ts,3)*pow(alpha,2)*beta*psi2a_prev-4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta*Ia_prev)*pow(kk,3)+((4*Lm*pow(Ts,2)*alpha*beta+8*pow(Ts,2)*alpha)*Ualpha+(4*Lm*pow(Ts,2)*alpha*beta+8*pow(Ts,2)*alpha)*Ua_prev+8*R1*pow(Ts,2)*alpha*beta*psi2a_prev-8*Lm*R1*pow(Ts,2)*alpha*beta*Ia_prev)*pow(kk,2)+(8*Ts*Ualpha+8*Ts*Ua_prev)*kk)*sigma+(R1*pow(Ts,4)*pow(omega,2)*Ualpha+(R1*pow(Ts,4)*Ua_prev-pow(R1,2)*pow(Ts,4)*Ia_prev)*pow(omega,2))*pow(kk,4)*pow(pn,2)+(R1*pow(Ts,4)*pow(alpha,2)*Ualpha+R1*pow(Ts,4)*pow(alpha,2)*Ua_prev-pow(R1,2)*pow(Ts,4)*pow(alpha,2)*Ia_prev)*pow(kk,4)+(4*R1*pow(Ts,3)*alpha*Ualpha+4*R1*pow(Ts,3)*alpha*Ua_prev-4*pow(R1,2)*pow(Ts,3)*alpha*Ia_prev)*pow(kk,3)+(4*R1*pow(Ts,2)*Ualpha+4*R1*pow(Ts,2)*Ua_prev-4*pow(R1,2)*pow(Ts,2)*Ia_prev)*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
        Ibeta=((((4*pow(Ts,2)*beta*psi2b_prev+4*pow(Ts,2)*Ib_prev)*pow(omega,2)+4*pow(Ts,2)*beta*omega_prev*psi2b_prev*omega)*pow(kk,2)*pow(pn,2)+((((4*pow(Ts,2)*alpha*beta-4*Lm*pow(Ts,2)*alpha*pow(beta,2))*psi2a_prev-8*Lm*pow(Ts,2)*alpha*beta*Ia_prev)*omega+(-4*Lm*pow(Ts,2)*alpha*pow(beta,2)-4*pow(Ts,2)*alpha*beta)*omega_prev*psi2a_prev)*pow(kk,2)+(-8*Ts*beta*psi2a_prev*omega-8*Ts*beta*omega_prev*psi2a_prev)*kk)*pn+((8*Lm*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*pow(Ts,2)*pow(alpha,2)*beta)*psi2b_prev-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)*Ib_prev+4*pow(Ts,2)*pow(alpha,2)*Ib_prev)*pow(kk,2)+(16*Ts*alpha*beta*psi2b_prev+16*Ts*alpha*Ib_prev)*kk+16*Ib_prev)*pow(sigma,2)+((pow(omega,2)*(pow(Ts,3)*(2*Ubeta+2*Ub_prev)+2*R1*pow(Ts,3)*beta*psi2b_prev)+2*R1*pow(Ts,3)*beta*omega_prev*psi2b_prev*omega)*pow(kk,3)*pow(pn,2)+((-2*Lm*pow(Ts,3)*alpha*beta*omega*Ualpha+(2*R1*pow(Ts,3)*alpha*beta*psi2a_prev-2*Lm*pow(Ts,3)*alpha*beta*Ua_prev)*omega-2*R1*pow(Ts,3)*alpha*beta*omega_prev*psi2a_prev)*pow(kk,3)+(-4*R1*pow(Ts,2)*beta*psi2a_prev*omega-4*R1*pow(Ts,2)*beta*omega_prev*psi2a_prev)*pow(kk,2))*pn+(pow(Ts,3)*pow(alpha,2)*beta*(Lm*(2*Ubeta+2*Ub_prev)-4*Lm*R1*Ib_prev)+pow(Ts,3)*pow(alpha,2)*(2*Ubeta+2*Ub_prev)+4*R1*pow(Ts,3)*pow(alpha,2)*beta*psi2b_prev)*pow(kk,3)+(pow(Ts,2)*alpha*beta*(Lm*(4*Ubeta+4*Ub_prev)-8*Lm*R1*Ib_prev)+pow(Ts,2)*alpha*(8*Ubeta+8*Ub_prev)+8*R1*pow(Ts,2)*alpha*beta*psi2b_prev)*pow(kk,2)+Ts*(8*Ubeta+8*Ub_prev)*kk)*sigma+pow(Ts,4)*pow(omega,2)*(R1*(Ubeta+Ub_prev)-pow(R1,2)*Ib_prev)*pow(kk,4)*pow(pn,2)+pow(Ts,4)*pow(alpha,2)*(R1*(Ubeta+Ub_prev)-pow(R1,2)*Ib_prev)*pow(kk,4)+pow(Ts,3)*alpha*(R1*(4*Ubeta+4*Ub_prev)-4*pow(R1,2)*Ib_prev)*pow(kk,3)+pow(Ts,2)*(R1*(4*Ubeta+4*Ub_prev)-4*pow(R1,2)*Ib_prev)*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
        psi2a=-((4*pow(Ts,2)*omega_prev*psi2a_prev*omega*pow(kk,2)*pow(pn,2)+((((4*Lm*pow(Ts,2)*alpha*beta-4*pow(Ts,2)*alpha)*psi2b_prev+8*Lm*pow(Ts,2)*alpha*Ib_prev)*omega+(4*Lm*pow(Ts,2)*alpha*beta+4*pow(Ts,2)*alpha)*omega_prev*psi2b_prev)*pow(kk,2)+(8*Ts*psi2b_prev*omega+8*Ts*omega_prev*psi2b_prev)*kk)*pn+((4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*psi2a_prev+(-8*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*beta-8*Lm*pow(Ts,2)*pow(alpha,2))*Ia_prev)*pow(kk,2)+(-16*Lm*Ts*alpha*beta*psi2a_prev-16*Lm*Ts*alpha*Ia_prev)*kk-16*psi2a_prev)*pow(sigma,2)+(4*R1*pow(Ts,3)*omega_prev*psi2a_prev*omega*pow(kk,3)*pow(pn,2)+((omega*(pow(Ts,3)*alpha*(Lm*(2*Ubeta+2*Ub_prev)+4*Lm*R1*Ib_prev)+(2*Lm*R1*pow(Ts,3)*alpha*beta-4*R1*pow(Ts,3)*alpha)*psi2b_prev)+(2*Lm*R1*pow(Ts,3)*alpha*beta+4*R1*pow(Ts,3)*alpha)*omega_prev*psi2b_prev)*pow(kk,3)+(8*R1*pow(Ts,2)*psi2b_prev*omega+8*R1*pow(Ts,2)*omega_prev*psi2b_prev)*pow(kk,2))*pn+((-2*pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta-2*Lm*pow(Ts,3)*pow(alpha,2))*Ualpha+(-2*pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta-2*Lm*pow(Ts,3)*pow(alpha,2))*Ua_prev+4*R1*pow(Ts,3)*pow(alpha,2)*psi2a_prev-4*Lm*R1*pow(Ts,3)*pow(alpha,2)*Ia_prev)*pow(kk,3)+(-4*Lm*pow(Ts,2)*alpha*Ualpha-4*Lm*pow(Ts,2)*alpha*Ua_prev-8*Lm*R1*pow(Ts,2)*alpha*beta*psi2a_prev-8*Lm*R1*pow(Ts,2)*alpha*Ia_prev)*pow(kk,2)-16*R1*Ts*psi2a_prev*kk)*sigma+pow(R1,2)*pow(Ts,4)*omega_prev*psi2a_prev*omega*pow(kk,4)*pow(pn,2)+((omega*(Lm*R1*pow(Ts,4)*alpha*(Ubeta+Ub_prev)-pow(R1,2)*pow(Ts,4)*alpha*psi2b_prev)+pow(R1,2)*pow(Ts,4)*alpha*omega_prev*psi2b_prev)*pow(kk,4)+(2*pow(R1,2)*pow(Ts,3)*psi2b_prev*omega+2*pow(R1,2)*pow(Ts,3)*omega_prev*psi2b_prev)*pow(kk,3))*pn+(-Lm*R1*pow(Ts,4)*pow(alpha,2)*Ualpha-Lm*R1*pow(Ts,4)*pow(alpha,2)*Ua_prev+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*psi2a_prev)*pow(kk,4)+(-2*Lm*R1*pow(Ts,3)*alpha*Ualpha-2*Lm*R1*pow(Ts,3)*alpha*Ua_prev)*pow(kk,3)-4*pow(R1,2)*pow(Ts,2)*psi2a_prev*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
        psi2b=-((4*pow(Ts,2)*omega_prev*psi2b_prev*omega*pow(kk,2)*pow(pn,2)+((((4*pow(Ts,2)*alpha-4*Lm*pow(Ts,2)*alpha*beta)*psi2a_prev-8*Lm*pow(Ts,2)*alpha*Ia_prev)*omega+(-4*Lm*pow(Ts,2)*alpha*beta-4*pow(Ts,2)*alpha)*omega_prev*psi2a_prev)*pow(kk,2)+(-8*Ts*psi2a_prev*omega-8*Ts*omega_prev*psi2a_prev)*kk)*pn+((4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*psi2b_prev-8*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*beta*Ib_prev-8*Lm*pow(Ts,2)*pow(alpha,2)*Ib_prev)*pow(kk,2)+(-16*Lm*Ts*alpha*beta*psi2b_prev-16*Lm*Ts*alpha*Ib_prev)*kk-16*psi2b_prev)*pow(sigma,2)+(4*R1*pow(Ts,3)*omega_prev*psi2b_prev*omega*pow(kk,3)*pow(pn,2)+((-2*Lm*pow(Ts,3)*alpha*omega*Ualpha+(-2*Lm*pow(Ts,3)*alpha*Ua_prev+(4*R1*pow(Ts,3)*alpha-2*Lm*R1*pow(Ts,3)*alpha*beta)*psi2a_prev-4*Lm*R1*pow(Ts,3)*alpha*Ia_prev)*omega+(-2*Lm*R1*pow(Ts,3)*alpha*beta-4*R1*pow(Ts,3)*alpha)*omega_prev*psi2a_prev)*pow(kk,3)+(-8*R1*pow(Ts,2)*psi2a_prev*omega-8*R1*pow(Ts,2)*omega_prev*psi2a_prev)*pow(kk,2))*pn+(pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta*(-2*Ubeta-2*Ub_prev)+pow(Ts,3)*pow(alpha,2)*(Lm*(-2*Ubeta-2*Ub_prev)-4*Lm*R1*Ib_prev)+4*R1*pow(Ts,3)*pow(alpha,2)*psi2b_prev)*pow(kk,3)+(pow(Ts,2)*alpha*(Lm*(-4*Ubeta-4*Ub_prev)-8*Lm*R1*Ib_prev)-8*Lm*R1*pow(Ts,2)*alpha*beta*psi2b_prev)*pow(kk,2)-16*R1*Ts*psi2b_prev*kk)*sigma+pow(R1,2)*pow(Ts,4)*omega_prev*psi2b_prev*omega*pow(kk,4)*pow(pn,2)+((-Lm*R1*pow(Ts,4)*alpha*omega*Ualpha+(pow(R1,2)*pow(Ts,4)*alpha*psi2a_prev-Lm*R1*pow(Ts,4)*alpha*Ua_prev)*omega-pow(R1,2)*pow(Ts,4)*alpha*omega_prev*psi2a_prev)*pow(kk,4)+(-2*pow(R1,2)*pow(Ts,3)*psi2a_prev*omega-2*pow(R1,2)*pow(Ts,3)*omega_prev*psi2a_prev)*pow(kk,3))*pn+(Lm*R1*pow(Ts,4)*pow(alpha,2)*(-Ubeta-Ub_prev)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*psi2b_prev)*pow(kk,4)+Lm*R1*pow(Ts,3)*alpha*(-2*Ubeta-2*Ub_prev)*pow(kk,3)-4*pow(R1,2)*pow(Ts,2)*psi2b_prev*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
    }
    else
    {
        Ualpha=0.0;
        Ubeta=0.0;
        omega=omega_prev;
        Ialpha=0.0;
        Ibeta=0.0;
        psi2a=0.0;
        psi2b=0.0;
    }

    p_akt_a = 3.0 / 2.0 * (Ualpha*Ialpha + Ubeta*Ibeta) / 3.0;
    p_akt_b = 3.0 / 2.0 * (Ualpha*Ialpha + Ubeta*Ibeta) / 3.0;
    p_akt_c = 3.0 / 2.0 * (Ualpha*Ialpha + Ubeta*Ibeta) / 3.0;

    i_dev_a = sqrt(pow(Ialpha, 2) + pow(Ibeta, 2)) / sqrt(2.0);
    i_dev_b = sqrt(pow(Ialpha, 2) + pow(Ibeta, 2)) / sqrt(2.0);
    i_dev_c = sqrt(pow(Ialpha, 2) + pow(Ibeta, 2)) / sqrt(2.0);
    u_dev_a = sqrt(pow(Ualpha, 2) + pow(Ubeta, 2)) / sqrt(2.0);
    u_dev_b = sqrt(pow(Ualpha, 2) + pow(Ubeta, 2)) / sqrt(2.0);
    u_dev_c = sqrt(pow(Ualpha, 2) + pow(Ubeta, 2)) / sqrt(2.0);

    //Расчет полных мощностей
    p_poln_a=i_dev_a*u_dev_a;
    p_poln_b=i_dev_a*u_dev_b;
    p_poln_c=i_dev_a*u_dev_c;

    //расчет реактивных мощностей
    p_reakt_a=sqrt(pow(p_poln_a,2)-pow(p_akt_a,2));
    p_reakt_b=sqrt(pow(p_poln_b,2)-pow(p_akt_b,2));
    p_reakt_c=sqrt(pow(p_poln_c,2)-pow(p_akt_c,2));

    //Расчет активных мощностей
    p_akt=p_akt_a+p_akt_b+p_akt_c;
    p_poln=p_poln_a+p_poln_b+p_poln_c;
    p_reakt=sqrt(pow(p_poln,2)-pow(p_akt,2));

    //Расчет коэффициентов мощности
    cos_f_a=p_akt_a/p_poln_a;
    cos_f_b=p_akt_b/p_poln_b;
    cos_f_c=p_akt_c/p_poln_c;
    cos_f=p_akt/p_poln;

    tepl_struct.P1=p_poln_a*cos_f_a+p_poln_b*cos_f_b+p_poln_c*cos_f_c;
    tepl_struct.dPdob=0.005*tepl_struct.P1;
    double Mel = 1.5*Lm*pn*(-psi2b*Ialpha+Ibeta*psi2a)/L2;
    M = Mel - 0.216 * omega*omega / 21780.0;
    //M = Mel - tepl_struct.dPdob / (omega + 0.01) - 0.216 * omega*omega / 21780.0;

    omega=omega_prev+0.5*kk*Ts*(M-Mc)/J+0.5*kk*Ts*(M-Mc)/J;

    tepl_struct.P2=omega*M;
    tepl_struct.dPel1=pow(i_dev_a,2)*R1 + pow(i_dev_b,2)*R1 + pow(i_dev_c,2)*R1;

    tepl_struct.kpd=tepl_struct.P2/tepl_struct.P1;
    tepl_struct.w_0=2*3.14*base.n_0/60;
    tepl_struct.Pelm=tepl_struct.w_0*Mel;
    tepl_struct.dPct=tepl_struct.P1-tepl_struct.Pelm-tepl_struct.dPel1;
    tepl_struct.dPel2=((tepl_struct.w_0-omega)/tepl_struct.w_0)*tepl_struct.Pelm;
    tepl_struct.dPmech=tepl_struct.Pelm-tepl_struct.dPel2-tepl_struct.P2 - tepl_struct.dPdob;

    Ua_prev = Ualpha;
    Ub_prev = Ubeta;
    omega_prev = omega;
    psi2a_prev = psi2a;
    psi2b_prev = psi2b;
    Ia_prev = Ialpha;
    Ib_prev = Ibeta;
}

void Model_el::timerTimeout()
{
    emit ready();
}

void Model_el::stop()
{
    timer.stop();
}
