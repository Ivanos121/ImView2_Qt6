#include "datasource_el.h"
#include <cmath>

DataSource_el::DataSource_el(double P_nom, double n_nom, double U_fnom,
                             double cosf_nom, double kpd_nom, double muk, double n_0)
{   
    double dP_mxnom,dP_dob,dP_nom,dP_per2nom,dP_pernom,dP_post,dP_per1nom;
    double I_1nom,s_nom,w_0,w_nom,M_nom,M_0,M_elmnom,M_elmax,K_z,bb,Z,X_k;
    double I_0,X10,dP_ct,Rm,sinf_0,Xm;

    // расчетная часть
    I_1nom=P_nom/(3*U_fnom*cosf_nom*kpd_nom); //Номинальный ток статора
    w_0=(2*3.14*n_0)/60; //Скорость идеального холостого хода
    w_nom=(2*3.14*n_nom)/60; //Номинальная скорость
    s_nom=(w_0-w_nom)/w_0; //номинальное скольжение
    M_nom=P_nom/w_nom; //Номинальный момент
    dP_nom=(P_nom*(1-kpd_nom))/kpd_nom; //Номинальные потери мощности
    dP_mxnom=0.05*dP_nom; //Номинальные механические потери мощности
    dP_dob=0.0281*dP_nom; //добавочные потери
    M_0=(dP_mxnom+dP_dob)/w_0; //Момент холостого хода
    M_elmnom=M_0+M_nom; //Номинальный электромагнитный момент
    dP_per2nom=M_elmnom*w_0*s_nom; //номинальные переменные потери в роторе
    K_z=0.61; //Коэффициент запаса
    dP_pernom=dP_nom/(1+pow(K_z,2)); //номинальные переменные потери мощности
    dP_post=dP_nom-dP_pernom; //Постоянные потери
    dP_per1nom=dP_pernom-dP_per2nom; //номинальные переменные потери в статоре
    R10=dP_per1nom/(3*I_1nom*I_1nom); //активное сопротивление фазы ротора

    M_elmax=muk*M_nom+M_0; //максимальный электромагнитный момент
    bb=((3*U_fnom*U_fnom*s_nom)/dP_per2nom)-2*R10; //коэффициент b
    Z=(3*U_fnom*U_fnom)/(2*w_0*M_elmax)-R10; //Сопротивление z
    R20=0.5*s_nom*(bb+sqrt(pow(bb,2)-4*pow(Z,2))); //приведенное активное сопротивление ротора
    X_k=sqrt(Z*Z-R10*R10); //Индуктивное сопротивление короткого замыкания
    //s_k=R20/Z; //критическое скольжение
    //aa=R10/R20; //коэффициент а
    //M=(2*M_elmax*(1+aa*s_k))/((s_nom/s_k)+(s_k/s_nom)+2*aa*s_k); //Электомагнитный момент при номинальном скольжении
    I_0=I_1nom*sqrt(1-pow(cosf_nom,2)); //ток холостого хода
    X10=0.5*X_k; //индуктивное сопротивление статора
    L10=X10/314; //Индуктивность рассеяния фазы статора
    dP_ct=dP_post-(dP_mxnom+dP_dob); //потери в стали
    Rm=dP_ct/(3*I_0*I_0); //Сопротивление потерь в стали
    sinf_0=sqrt(1-((R10+Rm)*I_0/U_fnom)*((R10+Rm)*I_0/U_fnom)); //??????
    Xm=U_fnom*sinf_0/I_0-X10; //индуктивное сопротивление взаимоиндукции
    Lm0=Xm/314; //Индуктивность рассеяния взаимоиндукции

    dataTimer2 = new QTimer(this);
    model = new ModelIdentf();
    connect(dataTimer2, &QTimer::timeout, this, &DataSource_el::read);
}

void DataSource_el::init()
{
    model->init(R10, R20, L10, L10, Lm0);
    dataTimer2->start(1000);
}

void DataSource_el::read()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        model->rasch();
        ua[i] = model->Ualpha;
        ub[i] = -1.0/2.0 * model->Ualpha + sqrt(3)/2.0*model->Ubeta;
        uc[i] = -1.0/2.0 * model->Ualpha - sqrt(3)/2.0*model->Ubeta;
        ia[i] = model->Ialpha;
        ib[i] = -1.0/2.0 * model->Ialpha + sqrt(3)/2.0*model->Ibeta;
        ic[i] = -1.0/2.0 * model->Ialpha - sqrt(3)/2.0*model->Ibeta;
        w[i] = model->omega;
    }
    emit ready();
}

void DataSource_el::stop()
{
    dataTimer2->stop();
}

