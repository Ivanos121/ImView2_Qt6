#ifndef NABLUDATELBASE_H
#define NABLUDATELBASE_H

#include "datasource.h"

class NabludatelBase
{
public:
    NabludatelBase() {};
    virtual void init(double, double, double, double, double) {};
    virtual void rasch(DataSource *) {};
    virtual double get_p_akt_a() {return 0.0;};
    virtual double get_p_akt_b() {return 0.0;};
    virtual double get_p_akt_c() {return 0.0;};
    virtual double get_p_akt() {return 0.0;};
    virtual double get_i_dev_a() {return 0.0;};
    virtual double get_i_dev_b() {return 0.0;};
    virtual double get_i_dev_c() {return 0.0;};
    virtual double get_u_dev_a() {return 0.0;};
    virtual double get_u_dev_b() {return 0.0;};
    virtual double get_u_dev_c() {return 0.0;};
    virtual double get_p_poln_a() {return 0.0;};
    virtual double get_p_poln_b() {return 0.0;};
    virtual double get_p_poln_c() {return 0.0;};
    virtual double get_p_poln() {return 0.0;};
    virtual double get_p_reakt_a() {return 0.0;};
    virtual double get_p_reakt_b() {return 0.0;};
    virtual double get_p_reakt_c() {return 0.0;};
    virtual double get_p_reakt() {return 0.0;};
    virtual double get_cos_f_a() {return 0.0;};
    virtual double get_cos_f_b() {return 0.0;};
    virtual double get_cos_f_c() {return 0.0;};
    virtual double get_cos_f() {return 0.0;};
    virtual double get_M_sr() {return 0.0;};
    virtual double get_Mc() {return 0.0;};
    virtual double get_w_sr() {return 0.0;};
    virtual double get_R2() {return 0.0;};    
    virtual double get_P1() {return 0.0;};
    virtual double get_dPel1() {return 0.0;};
    virtual double get_dPct() {return 0.0;};
    virtual double get_dPel2() {return 0.0;};
    virtual double get_dPmech() {return 0.0;};
    virtual double get_dPdob() {return 0.0;};
    virtual double get_P2() {return 0.0;};
    virtual double get_kpd() {return 0.0;};
    virtual double get_cosf() {return 0.0;};
    virtual double get_w_0() {return 0.0;};
    virtual double get_Pelm() {return 0.0;};    
    virtual void calcInternalParameters() {};    
};

#endif // NABLUDATEL_H
