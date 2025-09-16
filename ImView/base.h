#ifndef BASE_H
#define BASE_H

#include "qpoint.h"
#include <QString>
#include <QVector>

struct DigitOscParams
{
    QString portName;
    int speed;
    int data;
    int parity;
    int stopBits;
    int flowControl;
};

struct ArchieverParams
{
    QString portName;
    int speed;
    int data;
    int parity;
    int stopBits;
    int flowControl;
};

struct DigitMomentParams
{
    QString portName;
    int speed;
    int data;
    int parity;
    int stopBits;
    int flowControl;
};

struct PlcParams
{
    QString ipAddr;
    int port;
};

struct Base
{
    int P_nom;
    double n_nom;
    double U_fnom;
    double cosf_nom;
    double kpd_nom;
    double muk;
    double n_0;
    double J_dv;
    double R1;
    double R2;
    double L1;
    double L2;
    double Lm;
    double R11;
    double R21;
    QString dataSourceFilename;
    QString identfFilename;
    QString identfFilename_result;
    QString electromagnFilename;
    QString teplFilename;
    QString name;
    QString ki;
    double i_a;
    double u_a;
    double p_akt_a;
    double p_react_a;
    double p_poln_a;
    double cosf_a;
    double i_b;
    double u_b;
    double p_akt_b;
    double p_react_b;
    double p_poln_b;
    double cosf_b;
    double i_c;
    double u_c;
    double p_akt_c;
    double p_react_c;
    double p_poln_c;
    double cosf_c;
    double p_akt;
    double p_react;
    double p_poln;
    double cosf;
    double Mc_n;
    double Um;
    DigitOscParams digitOscParams;
    DigitMomentParams digitMomentParams;
    PlcParams plcParams;
    ArchieverParams archieverParams;
    QVector<QPointF> voltageData;
    QVector<QPointF> momentData;
    double lastPointX;
};

extern Base base;

#endif // BASE_H
