#ifndef BASE_TEPL_VENT_H
#define BASE_TEPL_VENT_H

#include <QString>
#include <QVector>

struct TeplParam
{
    double y_21;
    double y_22;
    double y_01;



};

struct VentParam
{
    QString name;
    double d1p;
    double d2p;
    double b;
    double n;
    double ro;
    double sotv;
    double s0;
    double s1;
    double a1;
    double s2;
    double a2;
    double s3;
    double s4;
    double fi;
    double fi2;
    double H0;
    double Qmax;
    double Z0;
    double Z1;
    double Z2;
    double Z3;
    double Z4;
    double Z5;
    double Z6;
    double Qp;
    double Hp;
    double Vcp;
    double Pvent;
    double epsilon1;
    double epsilon2;
    double epsilon3;
    double epsilon4;
    double epsilon5;
    double epsilon6;
    double cosf;
    double K;
    double nu2;
    double v;
    QString ventIdentfFileName;
    int Degree;
    int w_Q_inv_optimalDegree;
    int Q_H1_optimalDegree;
    int Q_H2_optimalDegree;
    int Q_Pv_optimalDegree;

    QVector<double> w_Q_inv_koeffss;
    QVector<double> Q_H1_koeffss;
    QVector<double> Q_H2_koeffss;
    QVector<double> Q_Pv_koeffss;

    QVector<double> Q_appr;
    QVector<double> H1_appr;
    QVector<double> H2_appr;
    QVector<double> Pv_appr;

};

struct VentParam2
{
    QString name;
    double d1p_2;
    double d2p_2;
    double b_2;
    double n_2;
    double ro_2;
    double sotv_2;
    double s1_2;
    double a1_2;
    double s2_2;
    double a2_2;
    double s3_2;
    double s4_2;
    double fi_2;
    double fi2_2;
    double H0_2;
    double Qmax_2;
    double Z0_2;
    double Z1_2;
    double Z2_2;
    double Z3_2;
    double Z4_2;
    double Z5_2;
    double Z6_2;
    double Qp_2;
    double Hp_2;
    double Vcp_2;
    double Pvent_2;
    double epsilon1_2;
    double epsilon2_2;
    double epsilon3_2;
    double epsilon4_2;
    double epsilon5_2;
    double epsilon6_2;
    double cosf_2;
    double K_2;
    double nu2_2;
    double v_2;
    QString ventIdentfFileName;
    int w_Q_inv_optimalDegree_2;
    int Q_H1_optimalDegree_2;
    int Q_H2_optimalDegree_2;
    int Q_Pv_optimalDegree_2;

    QVector<double> w_Q_inv_koeffss_2;
    QVector<double> Q_H1_koeffss_2;
    QVector<double> Q_H2_koeffss_2;
    QVector<double> Q_Pv_koeffss_2;
};

extern TeplParam teplparam;
extern VentParam ventparam;
extern VentParam2 ventparam2;

#endif // BASE_TEPL_VENT_H
