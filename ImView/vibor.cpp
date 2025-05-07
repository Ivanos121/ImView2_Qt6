#include "vibor.h"
#include <fstream>

std::ifstream fin,fin2, fin3, fin4;

Vibor::Vibor()
{

}
void Vibor::init()
{
    fin.open("uaa.txt",std::ios::in);
    fin >> X1_1 >> ua;

    fin2.open("iaa.txt",std::ios::in);
    fin2 >> X2_1 >> ia ;

    fin3.open("ibb.txt",std::ios::in);
    fin3 >> X3_1 >> r ;
    //fin2.close();

    fin4.open("ww.txt",std::ios::in);
    fin4 >> X4_1 >> w;
}

void Vibor::read()
{
    fin >> X1_1 >> ua;
    fin2 >> X2_1 >> ia;
    fin3 >> X3_1 >> r;
    fin4 >> X4_1 >> w;
}
