#ifndef INTENS_STAR_IZOL_H
#define INTENS_STAR_IZOL_H

struct Klass_A
{
    double G_A;
    double B_A;
};

struct Klass_B
{
    double G_B;
    double B_B;
};

struct Klass_C
{
    double G_C;
    double B_C;
};

struct Klass_E
{
    double G_E;
    double B_E;
};

struct Klass_F
{
    double G_F;
    double B_F;
};

struct Klass_H
{
    double G_H;
    double B_H;
};

struct Klass_izol
{
    Klass_A klass_A;
    Klass_B klass_B;
    Klass_C klass_C;
    Klass_E klass_E;
    Klass_F klass_F;
    Klass_H klass_H;
};

extern Klass_izol klass_izol;


#endif // INTENS_STAR_IZOL_H
