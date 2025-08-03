#ifndef IDENTF_KPEFF_H
#define IDENTF_KPEFF_H

#include <QVector>

struct KoeffBase {
    int koefff;
    virtual ~KoeffBase() = default; // виртуальный деструктор
    std::string name;
    QVector<QVector<double>> Koeff;
    int size;
    KoeffBase() : koefff(0), size(0) {}
};


struct Koeff_3000: public KoeffBase
{
    Koeff_3000()
    {
        koefff = 3000;                                    //синхронная частота вращения двигателя
        Koeff = {
            {1100, 1500, 2200, 3000, 4000, 5500, 7500, 11000, 15000, 18500},//Мощность двигателя
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},               //Коэффициент gd
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},               //Коэффициент gd
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},               //Коэффициент gd
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},               //Коэффициент gd
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},               //Коэффициент gd
            {1, 2, 3, 4, 5, 6, 6, 7, 8, 9}                //Коэффициент gd
        };
        name = "Koeff_3000";                              //Назрание структуры
        size = Koeff.size();                              //Размерность матрицы
    };
};

struct Koeff_1500: public KoeffBase
{
    Koeff_1500()
    {
        koefff = 1500;
        Koeff = {
        {1100, 1500, 2200, 3000, 4000, 5500, 7500, 11000, 15000, 18500},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9}
        };
        name = "Koeff_1500";
        size = Koeff.size();
    };
};

struct Koeff_1000: public KoeffBase
{
    //QVector<QVector<int>> Koeff;
    Koeff_1000()
    {
        koefff = 1000;
        Koeff = {
        {1100, 1500, 2200, 3000, 4000, 5500, 7500, 11000, 15000, 18500},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9}
        };
        name = "Koeff_1000";
        size = Koeff.size();
    };
};

struct Koeff_750: public KoeffBase
{
    Koeff_750()
    {
        koefff = 750;
        Koeff = {
        {1100, 1500, 2200, 3000, 4000, 5500, 7500, 11000, 15000, 18500},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 6, 7, 8, 9}
        };
        name = "Koeff_750";
        size = Koeff.size();

    };
};
struct Koeff_ad
{
    Koeff_3000 koeff_3000;
    Koeff_1500 koeff_1500;
    Koeff_1000 koeff_1000;
    Koeff_750  koeff_750;

    std::vector<std::reference_wrapper<KoeffBase>> allKoeffs;

    Koeff_ad()
    {
        allKoeffs.push_back(koeff_3000);
        allKoeffs.push_back(koeff_1500);
        allKoeffs.push_back(koeff_1000);
        allKoeffs.push_back(koeff_750);
    }
};

extern struct Koeff_ad koeff_ad;

#endif // IDENTF_KPEFF_H
