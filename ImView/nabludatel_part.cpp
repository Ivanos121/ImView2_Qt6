#include "nabludatel_part.h"
#include "base.h"
#include "math.h"
#include "device.h"

NabludatelPart::NabludatelPart()
{

}

void NabludatelPart::calcInternalParameters()
{
    sigma=L1-((Lm*Lm)/(L2));
    alpha=R2/L2;
    beta=Lm/(sigma*L2);

    b1=1/(sigma);
    b2=1/(sigma);
    a1=-(R1/sigma)-alpha*beta*Lm;
    a2=alpha*beta;
    a4=alpha*Lm;
    a5=-alpha;
    k=1.3;
    g1=(k-1)*(-(R1/sigma+alpha*beta*Lm)-alpha);
    cc=1/beta;
    g3=(k*k-1)*(-(R1/sigma+alpha*beta*Lm)*cc+alpha*Lm)-cc*(k-1)*(-R1/sigma-alpha*beta*Lm-alpha);
}

void NabludatelPart::init(double _R1, double _R2, double _L1, double _L2, double _Lm)
{
    R2p = 4.0;
    snom = 0.05;

    R1=_R1;
    R2 = _R2;
    R20 = _R2;
    L1 = _L1;
    L2 = _L2;
    Lm = _Lm;
    Lk0 = _L2 + _L1 - 2.0*Lm;
    //Lkp = (_L2 - Lm) / 1.0 + _L1 - Lm;
    Lkp = Lk0 / 1.3;

    calcInternalParameters();

    pn=2;
    J=0.01;
    Ia=0;
    Ib=0;
    psi2a=0;
    psi2b=0;
    Ua=0;
    Ub=0;
    t=0;
    M=0;
    Mc=0;
    kk=1;

    pn=2;
    kp=2;
    ki=40000;
    Kint=1.000082401231610;
    Ts=0.000032;
    Kint1=1;

    wizm = 0;
    ia = 0;
    ib = 0;
    psi1a=0;
    psi1b=0;
    psi2a = 0;
    psi2b = 0;
    M=0;
    t = 0;

    ia_prev=0.0;
    ib_prev=0.0;
    iaizm_prev=0.0;
    ibizm_prev=0.0;
    uaizm_prev=0.0;
    ubizm_prev=0.0;
    psi1a_prev=0.0;
    psi1b_prev=0.0;
    psi2a_prev=0.0;
    psi2b_prev=0.0;
}

void NabludatelPart::rasch(DataSource *dataSource)
{
    p_akt_a = 0.0;
    p_akt_b = 0.0;
    p_akt_c = 0.0;
    p_akt=0.0;
    i_dev_a=0.0;
    i_dev_b=0.0;
    i_dev_c=0.0;
    u_dev_a=0.0;
    u_dev_b=0.0;
    u_dev_c=0.0;
    p_poln_a=0.0;
    p_poln_b=0.0;
    p_poln_c=0.0;
    p_poln=0.0;
    p_reakt_a=0;
    p_reakt_b=0;
    p_reakt_c=0;
    p_reakt=0;
    cos_f_a=0.0;
    cos_f_b=0.0;
    cos_f_c=0.0;
    cos_f=0.0;
    M_sr = 0;
    w_sr = 0;

    double Ua_zero = 0.0;
    double Ub_zero = 0.0;
    double Uc_zero = 0.0;

    double Ia_zero = 0.0;
    double Ib_zero = 0.0;
    double Ic_zero = 0.0;

    for (int i = 0; i < BUF_SIZE; i++)
    {
        Ua_zero += dataSource->getUa()[i];
        Ub_zero += dataSource->getUb()[i];
        Uc_zero += dataSource->getUc()[i];

        Ia_zero += dataSource->getIa()[i];
        Ib_zero += dataSource->getIb()[i];
        Ic_zero += dataSource->getIc()[i];
    }

    Ua_zero /= BUF_SIZE;
    Ub_zero /= BUF_SIZE;
    Uc_zero /= BUF_SIZE;

    Ia_zero /= BUF_SIZE;
    Ib_zero /= BUF_SIZE;
    Ic_zero /= BUF_SIZE;

    for (int i = 0; i < BUF_SIZE; i++)
    {
    Ia = dataSource->getIb()[i];
    Ib = dataSource->getIa()[i];
    Ic = dataSource->getIc()[i];

    Ua = dataSource->getUb()[i];
    Ub = dataSource->getUa()[i];
    Uc = dataSource->getUc()[i];

    iaizm=sqrt(2.0/3.0)*(Ia-(Ib+Ic)/2.0);
    iaizm = iaCorrector.apply(iaizm,Kint,1.0,2.0,8.0,Ts);

    ibizm=(1/sqrt(2.0)) * (Ib - Ic);
    ibizm = ibCorrector.apply(ibizm,Kint,1.0,2.0,8.0,Ts);

    uaizm=sqrt(2.0/3.0)*(Ua-(Ub+Uc)/2.0);
    uaizm = uaCorrector.apply(uaizm,Kint,1.0,2.0,8.0,Ts);

    ubizm=(1/sqrt(2.0)) * (Ub - Uc);
    ubizm = ubCorrector.apply(ubizm,Kint,1.0,2.0,8.0,Ts);

    wizm = dataSource->getW()[i];

    a3=-pn*beta*wizm;
    a6=pn*wizm;
    g2=(k-1)*pn*wizm;
    g4=-cc*(k-1)*pn*wizm;

    ma11 = -0.5*Kint*Ts*g1+0.5*Kint*Ts*a1-1;
    ma12 = 0.5*Kint*Ts*g2;
    ma13 = 0.5*Kint*Ts*a2;
    ma14 = -0.5*Kint*Ts*a3;

    ma21 = -0.5*Kint*Ts*g2;
    ma22 = -0.5*Kint*Ts*g1+0.5*Kint*Ts*a1-1;
    ma23 = 0.5*Kint*Ts*a3;
    ma24 = 0.5*Kint*Ts*a2;

    ma31 = 0.5*Kint*Ts*a4-0.5*Kint*Ts*g3;
    ma32 = 0.5*Kint*Ts*g4;
    ma33 = 0.5*Kint*Ts*a5-1;
    ma34 = -0.5*Kint*Ts*a6;

    ma41 = -0.5*Kint*Ts*g4;
    ma42 = 0.5*Kint*Ts*a4-0.5*Kint*Ts*g3;
    ma43 = 0.5*Kint*Ts*a6;
    ma44 = 0.5*Kint*Ts*a5-1;

    ba1 = -(Kint*Ts*b1*uaizm-Kint*Ts*g2*ibizm+Kint*Ts*g1*iaizm+Kint*Ts*b1*uaizm_prev-Kint*Ts*a3*psi2b_prev+Kint*Ts*a2*psi2a_prev-Kint*Ts*g2*ibizm_prev+Kint*Ts*g2*ib_prev+Kint*Ts*g1*iaizm+(-Kint*Ts*g1+Kint*Ts*a1+2)*ia_prev)/(2);
    ba2 = -(Kint*Ts*b2*ubizm+Kint*Ts*g1*ibizm+Kint*Ts*g2*iaizm+Kint*Ts*b2*ubizm_prev+Kint*Ts*a2*psi2b_prev+Kint*Ts*a3*psi2a_prev+Kint*Ts*g1*ibizm_prev+(-Kint*Ts*g1+Kint*Ts*a1+2)*ib_prev+Kint*Ts*g2*iaizm-Kint*Ts*g2*ia_prev)/(2);
    ba3 = (Kint*Ts*g4*ibizm-Kint*Ts*g3*iaizm+Kint*Ts*a6*psi2b_prev+(-Kint*Ts*a5-2)*psi2a_prev+Kint*Ts*g4*ibizm_prev-Kint*Ts*g4*ib_prev-Kint*Ts*g3*iaizm+(Kint*Ts*g3-Kint*Ts*a4)*ia_prev)/(2);
    ba4 = -(Kint*Ts*g3*ibizm+Kint*Ts*g4*iaizm+(Kint*Ts*a5+2)*psi2b_prev+Kint*Ts*a6*psi2a_prev+Kint*Ts*g3*ibizm_prev+(Kint*Ts*a4-Kint*Ts*g3)*ib_prev+Kint*Ts*g4*iaizm-Kint*Ts*g4*ia_prev)/(2);

    t=t+Ts;

    ia = (((ba1*ma22-ba2*ma12)*ma33+(ba2*ma13-ba1*ma23)*ma32+ba3*ma12*ma23-ba3*ma13*ma22)*ma44+((ba2*ma12-ba1*ma22)*ma34+(ba1*ma24-ba2*ma14)*ma32-ba3*ma12*ma24+ba3*ma14*ma22)*ma43+((ba1*ma23-ba2*ma13)*ma34+(ba2*ma14-ba1*ma24)*ma33+ba3*ma13*ma24-ba3*ma14*ma23)*ma42+(ba4*ma13*ma22-ba4*ma12*ma23)*ma34+(ba4*ma12*ma24-ba4*ma14*ma22)*ma33+(ba4*ma14*ma23-ba4*ma13*ma24)*ma32)/(((ma11*ma22-ma12*ma21)*ma33+(ma13*ma21-ma11*ma23)*ma32+(ma12*ma23-ma13*ma22)*ma31)*ma44+((ma12*ma21-ma11*ma22)*ma34+(ma11*ma24-ma14*ma21)*ma32+(ma14*ma22-ma12*ma24)*ma31)*ma43+((ma11*ma23-ma13*ma21)*ma34+(ma14*ma21-ma11*ma24)*ma33+(ma13*ma24-ma14*ma23)*ma31)*ma42+((ma13*ma22-ma12*ma23)*ma34+(ma12*ma24-ma14*ma22)*ma33+(ma14*ma23-ma13*ma24)*ma32)*ma41);
    ib = -(((ba1*ma21-ba2*ma11)*ma33+(ba2*ma13-ba1*ma23)*ma31+ba3*ma11*ma23-ba3*ma13*ma21)*ma44+((ba2*ma11-ba1*ma21)*ma34+(ba1*ma24-ba2*ma14)*ma31-ba3*ma11*ma24+ba3*ma14*ma21)*ma43+((ba1*ma23-ba2*ma13)*ma34+(ba2*ma14-ba1*ma24)*ma33+ba3*ma13*ma24-ba3*ma14*ma23)*ma41+(ba4*ma13*ma21-ba4*ma11*ma23)*ma34+(ba4*ma11*ma24-ba4*ma14*ma21)*ma33+(ba4*ma14*ma23-ba4*ma13*ma24)*ma31)/(((ma11*ma22-ma12*ma21)*ma33+(ma13*ma21-ma11*ma23)*ma32+(ma12*ma23-ma13*ma22)*ma31)*ma44+((ma12*ma21-ma11*ma22)*ma34+(ma11*ma24-ma14*ma21)*ma32+(ma14*ma22-ma12*ma24)*ma31)*ma43+((ma11*ma23-ma13*ma21)*ma34+(ma14*ma21-ma11*ma24)*ma33+(ma13*ma24-ma14*ma23)*ma31)*ma42+((ma13*ma22-ma12*ma23)*ma34+(ma12*ma24-ma14*ma22)*ma33+(ma14*ma23-ma13*ma24)*ma32)*ma41);
    psi2a = (((ba1*ma21-ba2*ma11)*ma32+(ba2*ma12-ba1*ma22)*ma31+ba3*ma11*ma22-ba3*ma12*ma21)*ma44+((ba2*ma11-ba1*ma21)*ma34+(ba1*ma24-ba2*ma14)*ma31-ba3*ma11*ma24+ba3*ma14*ma21)*ma42+((ba1*ma22-ba2*ma12)*ma34+(ba2*ma14-ba1*ma24)*ma32+ba3*ma12*ma24-ba3*ma14*ma22)*ma41+(ba4*ma12*ma21-ba4*ma11*ma22)*ma34+(ba4*ma11*ma24-ba4*ma14*ma21)*ma32+(ba4*ma14*ma22-ba4*ma12*ma24)*ma31)/(((ma11*ma22-ma12*ma21)*ma33+(ma13*ma21-ma11*ma23)*ma32+(ma12*ma23-ma13*ma22)*ma31)*ma44+((ma12*ma21-ma11*ma22)*ma34+(ma11*ma24-ma14*ma21)*ma32+(ma14*ma22-ma12*ma24)*ma31)*ma43+((ma11*ma23-ma13*ma21)*ma34+(ma14*ma21-ma11*ma24)*ma33+(ma13*ma24-ma14*ma23)*ma31)*ma42+((ma13*ma22-ma12*ma23)*ma34+(ma12*ma24-ma14*ma22)*ma33+(ma14*ma23-ma13*ma24)*ma32)*ma41);
    psi2b = -(((ba1*ma21-ba2*ma11)*ma32+(ba2*ma12-ba1*ma22)*ma31+ba3*ma11*ma22-ba3*ma12*ma21)*ma43+((ba2*ma11-ba1*ma21)*ma33+(ba1*ma23-ba2*ma13)*ma31-ba3*ma11*ma23+ba3*ma13*ma21)*ma42+((ba1*ma22-ba2*ma12)*ma33+(ba2*ma13-ba1*ma23)*ma32+ba3*ma12*ma23-ba3*ma13*ma22)*ma41+(ba4*ma12*ma21-ba4*ma11*ma22)*ma33+(ba4*ma11*ma23-ba4*ma13*ma21)*ma32+(ba4*ma13*ma22-ba4*ma12*ma23)*ma31)/(((ma11*ma22-ma12*ma21)*ma33+(ma13*ma21-ma11*ma23)*ma32+(ma12*ma23-ma13*ma22)*ma31)*ma44+((ma12*ma21-ma11*ma22)*ma34+(ma11*ma24-ma14*ma21)*ma32+(ma14*ma22-ma12*ma24)*ma31)*ma43+((ma11*ma23-ma13*ma21)*ma34+(ma14*ma21-ma11*ma24)*ma33+(ma13*ma24-ma14*ma23)*ma31)*ma42+((ma13*ma22-ma12*ma23)*ma34+(ma12*ma24-ma14*ma22)*ma33+(ma14*ma23-ma13*ma24)*ma32)*ma41);

    R2 = R2_prev-kp*ia*psi2b+kp*iaizm*psi2b+kp*ib*psi2a-kp*ibizm*psi2a+kp*ia_prev*psi2b_prev-kp*iaizm*psi2b_prev-kp*ib_prev*psi2a_prev+kp*ibizm_prev*psi2a_prev-.5000000000*Kint*Ts*ki*ia*psi2b+.5000000000*Kint*Ts*ki*iaizm*psi2b+.5000000000*Kint*Ts*ki*ib*psi2a-.5000000000*Kint*Ts*ki*ibizm*psi2a-0.5000000000*Kint*Ts*ki*ia_prev*psi2b_prev+.5000000000*Kint*Ts*ki*iaizm*psi2b_prev+.5000000000*Kint*Ts*ki*ib_prev*psi2a_prev-.5000000000*Kint*Ts*ki*ibizm_prev*psi2a_prev;

    psi1a=(Kint1*Ts*uaizm-Kint1*R1*Ts*iaizm+Kint1*Ts*uaizm_prev+2*psi1a_prev-Kint1*R1*Ts*iaizm_prev)/2;
    psi1b=(Kint1*Ts*ubizm-Kint1*R1*Ts*ibizm+Kint1*Ts*ubizm_prev+2*psi1b_prev-Kint1*R1*Ts*ibizm_prev)/2;
    M = (psi1b*iaizm-psi1a*ibizm)*(-3/2*pn);
    M_sr += M;
    //M_sr += ia*ia;
    w_sr += wizm;

    R2_prev = R2;
    ia_prev=ia;
    ib_prev=ib;
    iaizm_prev=iaizm;
    ibizm_prev=ibizm;
    uaizm_prev=uaizm;
    ubizm_prev=ubizm;
    psi1a_prev=psi1a;
    psi1b_prev=psi1b;
    psi2a_prev=psi2a;
    psi2b_prev=psi2b;

        p_akt_a += dataSource->getUa()[i]*dataSource->getIa()[i];
        p_akt_b += dataSource->getUb()[i]*dataSource->getIb()[i];
        p_akt_c += dataSource->getUc()[i]*dataSource->getIc()[i];
        i_dev_a += pow(dataSource->getIa()[i],2);
        i_dev_b += pow(dataSource->getIb()[i],2);
        i_dev_c += pow(dataSource->getIc()[i],2);
        u_dev_a += pow(dataSource->getUa()[i],2);
        u_dev_b += pow(dataSource->getUb()[i],2);
        u_dev_c += pow(dataSource->getUc()[i],2);

    }

    M_sr /= BUF_SIZE;
    w_sr /= BUF_SIZE;

    double deltaR2 = (R2p - R20)/(1-snom);
    double w0 = 2.0*M_PI*50.0/pn;
    double s = (w0 - w_sr)/w0;

    if (s > 1)
    {
        //R2 = R2p;
        L2 = Lkp + Lm - (L1 - Lm);
    }
    else if (s < snom)
    {
        //R2 = R20;
        L2 = Lk0 + Lm - (L1 - Lm);
    }
    else
    {
        //R2 = R20 + deltaR2*(s - snom);

        double d = Lk0 / Lkp;
        double k = (d-1.0)/(1.0 - snom);
        double k1 = 1.0 - k*snom;
        double Lk = Lk0 / (k1 + k*s);

        L2 = Lm + Lk - (L1 - Lm);
    }

    calcInternalParameters();

    //printf("R2 = %g L2 = %g s=%g\n", R2, L2,s);

    sigma=L1-((Lm*Lm)/(L2));
    alpha=R2/L2;
    beta=Lm/(sigma*L2);

    //Расчет активных мощностей
    p_akt_a /= BUF_SIZE;
    p_akt_b /= BUF_SIZE;
    p_akt_c /= BUF_SIZE;

    //Расчет действующих значений токов
    i_dev_a /= BUF_SIZE;
    i_dev_a = sqrt(i_dev_a);
    i_dev_b /= BUF_SIZE;
    i_dev_b = sqrt(i_dev_b);
    i_dev_c /= BUF_SIZE;
    i_dev_c = sqrt(i_dev_c);

    //Расчет действующих значений напряжений
    u_dev_a /= BUF_SIZE;
    u_dev_a = sqrt(u_dev_a);
    u_dev_b /= BUF_SIZE;
    u_dev_b = sqrt(u_dev_b);
    u_dev_c /= BUF_SIZE;
    u_dev_c = sqrt(u_dev_c);

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

    P1=p_akt_a + p_akt_b + p_akt_c;
    dPdob=0.005*P1;
    dPmech = 0.005*P1;
    double Mel = M_sr;
    double M_meh = Mel - (dPdob + dPmech) / w_sr;

    P2=w_sr*M_meh;
    dPel1=pow(i_dev_a,2)*R1 + pow(i_dev_b,2)*R1 + pow(i_dev_c,2)*R1;

    kpd=P2/P1;
    w_0=2*3.14*base.n_0/60;
    Pelm=w_0*Mel;
    dPct=P1-Pelm-dPel1;
    dPel2=((w_0-w_sr)/w_0)*Pelm;
}


