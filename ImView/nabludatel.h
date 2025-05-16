#ifndef NABLUDATEL_H
#define NABLUDATEL_H

#include "datasource.h"
#include "nabludatel_base.h"
#include "zerocorrector.h"

class Nabludatel : public NabludatelBase
{
public:
    Nabludatel();
    void init(double _R1, double _R2, double _L1, double _L2, double _Lm) override;
    void rasch(DataSource *dataSourceBVAS) override;
    double get_p_akt_a() override {return p_akt_a;} ;
    double get_p_akt_b() override {return p_akt_b;};
    double get_p_akt_c() override {return p_akt_c;} ;
    double get_p_akt() override {return p_akt;} ;
    double get_i_dev_a() override {return i_dev_a;} ;
    double get_i_dev_b() override {return i_dev_b;} ;
    double get_i_dev_c() override {return i_dev_c;} ;
    double get_u_dev_a() override {return u_dev_a;} ;
    double get_u_dev_b() override {return u_dev_b;} ;
    double get_u_dev_c() override {return u_dev_c;} ;
    double get_p_poln_a() override {return p_poln_a;} ;
    double get_p_poln_b() override {return p_poln_b;} ;
    double get_p_poln_c() override {return p_poln_c;} ;
    double get_p_poln() override {return p_poln;} ;
    double get_p_reakt_a() override {return p_reakt_a;} ;
    double get_p_reakt_b() override {return p_reakt_b;} ;
    double get_p_reakt_c() override {return p_reakt_c;} ;
    double get_p_reakt() override {return p_reakt;} ;
    double get_cos_f_a() override {return cos_f_a;} ;
    double get_cos_f_b() override {return cos_f_b;} ;
    double get_cos_f_c() override {return cos_f_c;} ;
    double get_cos_f() override {return cos_f;} ;
    double get_M_sr() override {return M_sr;} ;
    double get_Mc() override {return Mc;} ;
    double get_w_sr() override {return w_sr;} ;
    double get_P1() override {return P1;} ;
    double get_dPel1() override {return dPel1;} ;
    double get_dPct() override {return dPct;} ;
    double get_dPel2() override {return dPel2;} ;
    double get_dPmech() override {return dPmech;} ;
    double get_dPdob() override {return dPdob;} ;
    double get_P2() override {return P2;} ;
    double get_kpd() override {return kpd;} ;
    double get_cosf() override {return cosf;} ;
    double get_w_0() override {return w_0;} ;
    double get_Pelm() override {return Pelm;} ;
    ZeroCorrector uaCorrector;
    ZeroCorrector ubCorrector;
    ZeroCorrector iaCorrector;
    ZeroCorrector ibCorrector;

private:
    double Ua, Ub, Uc, Ia, Ib, Ic, sigma,alpha, beta, kk, Ts, t, M, Mc;
    double R1, R2, R20, L1, L2, Lkp, Lk0, Lm, J, pn, R2p, snom;    
    double a1,a2,a3,a4,a5,a6,b1,b2,g1,g2,g3,g4,k,cc,Kint,ba1,ba2,ba3,ba4,Kint1,kp,ki;
    double ma11,ma12,ma13,ma14,ma21,ma22,ma23,ma24,ma31,ma32,ma33,ma34,ma41,ma42,ma43,ma44;
    double w, w_prev,ua,ub,ia,ib,psi1a,psi1a_prev,psi1b,psi1b_prev,iaizm,iaizm_prev,ibizm,ibizm_prev,uaizm,uaizm_prev,ubizm,ubizm_prev,
        psi2a,psi2a_prev,psi2b,psi2b_prev,ia_prev,ib_prev;
    double p_akt_a, p_akt_b, p_akt_c, p_akt, i_dev_a, i_dev_b, i_dev_c, u_dev_a, u_dev_b, u_dev_c,
        p_poln_a, p_poln_b, p_poln_c, p_poln, p_reakt_a, p_reakt_b, p_reakt_c=0, p_reakt, cos_f_a,
        cos_f_b, cos_f_c, cos_f, M_sr, w_sr;
    double P1, dPel1,dPct,dPel2,dPmech,dPdob,P2,kpd,cosf, w_0, Pelm;    
    void calcInternalParameters() override;
};

#endif // NABLUDATEL_H
