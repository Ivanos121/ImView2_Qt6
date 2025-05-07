#include "model.h"
#include <QDebug>
#include <QSettings>
#include <cmath>
#include "device.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <base.h>
#include <QDir>

double X1,X2,X3,X4,b,d,psia_nev,g,k,l,m,n,o,p,q,t,u,sigma,alfa;
double R2_1,L_1,Lm_1;
double kpsi, pn, ki, R1,kk, Ts, gpsi, gd, gb, gp;

Model::Model()
{

}

void Model::init(double P_nom, double n_nom, double U_fnom,
          double cosf_nom, double kpd_nom, double muk, double n_0, double _gd, double _gb, double _gp,
                 double _ki, double _kpsi, double _gpsi)
{
    double dP_mxnom,dP_dob,dP_nom,dP_per2nom,dP_pernom,dP_post,dP_per1nom;
    double I_1nom,s_nom,w_0,w_nom,M_nom,M_0,M_elmnom,M_elmax,K_z,R10,bb,Z,R20,X_k,s_k, M_snom, aa,dm;
    double I_0,X10,dP_ct,L10,Rm,sinf_0,Xm,Lm0;
    gb=_gb;
    gd=_gd;
    gp=_gp;
    ki=_ki;
    kpsi=_kpsi;
    gpsi=_gpsi;


   //Чтение данных


   // расчетная часть
   I_1nom=P_nom/(3*U_fnom*cosf_nom*kpd_nom); //Номинальный ток статора
   w_0=(2*M_PI*n_0)/60; //Скорость идеального холостого хода
   w_nom=(2*M_PI*n_nom)/60; //Номинальная скорость
   s_nom=(w_0-w_nom)/w_0; //номинальное скольжение
   M_nom=P_nom/w_nom; //Номинальный момент
   dP_nom=(P_nom*(1-kpd_nom))/kpd_nom; //Номинальные потери мощности
   dP_mxnom=0.05*dP_nom; //Номинальные механические потери мощности
   dP_dob=0.0281*dP_nom; //добавочные потери
   M_0=(dP_mxnom+dP_dob)/w_0; //Момент холостого хода
   M_elmnom=M_0+M_nom; //Номинальный электромагнитный момент
   dP_per2nom=M_elmnom*w_0*s_nom; //номинальные переменные потери в роторе

   //L1:
   //QSettings settings( "BRU", "IM View");
   //K_z = settings.value( "kz", "").toDouble();
   K_z=0.61; //Коэффициент запаса
   dP_pernom=dP_nom/(1+pow(K_z,2)); //номинальные переменные потери мощности
   dP_post=dP_nom-dP_pernom; //Постоянные потери
   dP_per1nom=dP_pernom-dP_per2nom; //номинальные переменные потери в статоре
   R10=dP_per1nom/(3*I_1nom*I_1nom); //активное сопротивление фазы ротора
   M_elmax=muk*M_nom+M_0; //максимальный электромагнитный момент
   bb=((3*U_fnom*U_fnom*s_nom)/dP_per2nom)-2*R10; //коэффициент b
   Z=((3*U_fnom*U_fnom)/(2*w_0*M_elmax))-R10; //Сопротивление z
   R20=0.5*s_nom*(bb+sqrt(pow(bb,2)-4*pow(Z,2))); //приведенное активное сопротивление ротора
   X_k=sqrt(Z*Z-R10*R10); //Индуктивное сопротивление короткого замыкания
   s_k=R20/Z; //критическое скольжение
   aa=R10/R20; //коэффициент а
   M_snom=(2*M_elmax*(1+aa*s_k))/((s_nom/s_k)+(s_k/s_nom)+2*aa*s_k); //Электомагнитный момент при номинальном скольжении
   dm=(M_snom-M_elmnom)/M_snom;
   /*if(dm<0.005)
   {
       QSettings settings( "BRU", "IM View");
       settings.setValue( "kz", K_z + 0.05);
       goto L1;
   }
   else if(dm>0.05)
   {
       QSettings settings( "BRU", "IM View");
       settings.setValue( "kz", K_z - 0.05);
       goto L1;
   }
   else goto L2;
   L2:*/
   I_0=I_1nom*sqrt(1-pow(cosf_nom,2)); //ток холостого хода
   X10=0.5*X_k; //индуктивное сопротивление статора
   L10=X10/314; //Индуктивность рассеяния фазы статора
   dP_ct=dP_post-(dP_mxnom+dP_dob); //потери в стали
   Rm=dP_ct/(3*I_0*I_0); //Сопротивление потерь в стали
   sinf_0=sqrt(1-((R10+Rm)*I_0/U_fnom)*((R10+Rm)*I_0/U_fnom)); //??????
   Xm=(U_fnom*sinf_0/I_0)-X10; //индуктивное сопротивление взаимоиндукции
   Lm0=Xm/314; //Индуктивность рассеяния взаимоиндукции
   L10 = L10 + Lm0;

   //инициализация начальных значений
   sigma=L10-pow(Lm0,2)/L10;
   alfa = R20/L10;
   p=alfa*L10/sigma;
   d=1.0/sigma;
   b=alfa/sigma;
   psia_nev=0.01;
   g=0.01;
   k=0.01;
   l=0.01;
   m=0.01;
   n=0.01;
   o=0.01;
   q=0.01;
   t=0.01;
   u=0.01;
   L=L10;
   Lm=Lm0;
   R2=R20;
   //gd=50;
   //gb=8000;
   //gp=100;
   //ki=2;
   pn=2;
   //kpsi=0.005;
   R1=R10;
   //gpsi=1;
   kk=1;
   }

void Model::rasch(DataSource *dataSource)
{
    QString filename = "result_identf_2.csv";
    QString setpath = "../Output";
    std::ofstream fout;
    base.identfFilename_result = setpath+QDir::separator()+filename;

    fout.open(QString(base.identfFilename_result).toStdString(),std::ios::out | std::ios_base::app);

    //fout << "psia_nev" << " " << "o" << " " << "n" << std::endl;

    fout << "psia_nev" << " " << "i_alfa" << " " << "i_beta" << " " << "u_alfa" << " " << "u_beta" << " " << "m"
         << " " << "g" << " " << "l"      << " " << "k"      << " " << "p"      << " " << "d"      << " " << "b"
         << " " << "t" << " " << "n"      << " " << "o"      << " " << "u"      << " " << "q"      << " " << "R1"
         << " " << "R2" << " " << "L"     << " " << "Lm"     << " " << "w"      << std::endl;

    for (int i = 0; i < BUF_SIZE; i++)
    {
        double Ts=0.0001;
        double u_alfa = dataSource->getUa()[i];
        double u_beta = 1.0/sqrt(3)*(dataSource->getUa()[i] + 2*dataSource->getUb()[i]);
        double i_alfa = dataSource->getIa()[i];
        double i_beta = 1.0/sqrt(3)*(dataSource->getIa()[i] + 2*dataSource->getIb()[i]);

        psia_nev = psia_nev+(-R1*i_alfa+u_alfa+kpsi*m)*kk*Ts;

        g = g+(-R1*i_beta+u_beta+kpsi*l)*kk*Ts;
        k = k+(-(p+R1*d)*k-dataSource->getW()[i]*pn*l+b*psia_nev+d*dataSource->getW()[i]*pn*g+d*u_alfa+ki*m+d*dataSource->getW()[i]*pn*t)*kk*Ts;
        l = l+(-(p+R1*d)*l+dataSource->getW()[i]*pn*k+b*g-d*dataSource->getW()[i]*pn*psia_nev+d*u_beta+ki*n-d*dataSource->getW()[i]*pn*o)*kk*Ts;
        b = b+gb*(psia_nev*m+g*n)*kk*Ts; // сильно
        d = d+gd*(u*m+q*n)*kk*Ts; // сильно
        p = p-gp*(k*m+l*n)*kk*Ts;
        o = o+(-kpsi*m-gpsi*dataSource->getW()[i]*pn*n)*kk*Ts; // слабо
        t = t+(-kpsi*n+gpsi*dataSource->getW()[i]*pn*m)*kk*Ts; // слабо
        m = i_alfa - k;
        n = i_beta - l;
        u = -R1*k+dataSource->getW()[i]*pn*g+dataSource->getW()[i]*pn*t+u_alfa;
        q = -R1*l-dataSource->getW()[i]*pn*psia_nev-dataSource->getW()[i]*pn*o+u_beta;
        sigma=1/d;
        alfa = b*sigma;
        L=(p*sigma)/alfa;
        Lm=sqrt(L*(L-sigma));
        R2=alfa*L;

        fout << psia_nev   << " " << i_alfa   << " " << i_beta   << " " << u_alfa   << " " << u_beta   << " " << m
             << " " << g   << " " << l        << " " << k        << " " << p        << " " << d        << " " << b
             << " " << t   << " " << n        << " " << o        << " " << u        << " " << q        << " " << R1
             << " " << R2  << " " << L        << " " << Lm       << " " << dataSource->getW()[i]       << std::endl;
    }

    fout.close();
}

