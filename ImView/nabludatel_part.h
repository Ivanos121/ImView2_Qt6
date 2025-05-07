#ifndef NABLUDATEL_PART_H
#define NABLUDATEL_PART_H

#include "datasource.h"
#include "nabludatel_base.h"
#include "zerocorrector.h"

class NabludatelPart : public NabludatelBase
{
public:
    NabludatelPart();
    virtual void init(double _R1, double _R2, double _L1, double _L2, double _Lm);
    virtual void rasch(DataSource *dataSourceBVAS);

    virtual double get_p_akt_a() {return p_akt_a;};
    virtual double get_p_akt_b() {return p_akt_b;};
    virtual double get_p_akt_c() {return p_akt_c;};
    virtual double get_p_akt() {return p_akt;};
    virtual double get_i_dev_a() {return i_dev_a;};
    virtual double get_i_dev_b() {return i_dev_b;};
    virtual double get_i_dev_c() {return i_dev_c;};
    virtual double get_u_dev_a() {return u_dev_a;};
    virtual double get_u_dev_b() {return u_dev_b;};
    virtual double get_u_dev_c() {return u_dev_c;};
    virtual double get_p_poln_a() {return p_poln_a;};
    virtual double get_p_poln_b() {return p_poln_b;};
    virtual double get_p_poln_c() {return p_poln_c;};
    virtual double get_p_poln() {return p_poln;};
    virtual double get_p_reakt_a() {return p_reakt_a;};
    virtual double get_p_reakt_b() {return p_reakt_b;};
    virtual double get_p_reakt_c() {return p_reakt_c;};
    virtual double get_p_reakt() {return p_reakt;};
    virtual double get_cos_f_a() {return cos_f_a;};
    virtual double get_cos_f_b() {return cos_f_b;};
    virtual double get_cos_f_c() {return cos_f_c;};
    virtual double get_cos_f() {return cos_f;};
    virtual double get_M_sr() {return M_sr;};
    virtual double get_Mc() {return Mc;};
    virtual double get_w_sr() {return w_sr;};
    virtual double get_R2() {return R2;};

    virtual double get_P1() {return P1;};
    virtual double get_dPel1() {return dPel1;};
    virtual double get_dPct() {return dPct;};
    virtual double get_dPel2() {return dPel2;};
    virtual double get_dPmech() {return dPmech;};
    virtual double get_dPdob() {return dPdob;};
    virtual double get_P2() {return P2;};
    virtual double get_kpd() {return kpd;};
    virtual double get_cosf() {return cosf;};
    virtual double get_w_0() {return w_0;};
    virtual double get_Pelm() {return Pelm;};

    ZeroCorrector uaCorrector;
    ZeroCorrector ubCorrector;
    ZeroCorrector iaCorrector;
    ZeroCorrector ibCorrector;

private:
    double Ua, Ub, Uc, Ia, Ib, Ic, sigma,alpha, beta, kk, Ts, t, M, Mc;
    double R1, R2, R2_prev, R20, L1, L2, Lkp, Lk0, Lm, J, pn, R2p, snom;

    double a1,a2,a3,a4,a5,a6,b1,b2,g1,g2,g3,g4,k,cc,Kint,ba1,ba2,ba3,ba4,Kint1,kp,ki;
    double ma11,ma12,ma13,ma14,ma21,ma22,ma23,ma24,ma31,ma32,ma33,ma34,ma41,ma42,ma43,ma44;
    double wizm, ua,ub,ia,ib,psi1a,psi1a_prev,psi1b,psi1b_prev,iaizm,iaizm_prev,ibizm,ibizm_prev,uaizm,uaizm_prev,ubizm,ubizm_prev,
        psi2a,psi2a_prev,psi2b,psi2b_prev,ia_prev,ib_prev;

    double p_akt_a, p_akt_b, p_akt_c, p_akt, i_dev_a, i_dev_b, i_dev_c, u_dev_a, u_dev_b, u_dev_c,
        p_poln_a, p_poln_b, p_poln_c, p_poln, p_reakt_a, p_reakt_b, p_reakt_c=0, p_reakt, cos_f_a,
        cos_f_b, cos_f_c, cos_f, M_sr, w_sr;
    double P1, dPel1,dPct,dPel2,dPmech,dPdob,P2,kpd,cosf, w_0, Pelm;

    void calcInternalParameters();

};



#endif // NABLUDATEL_H

