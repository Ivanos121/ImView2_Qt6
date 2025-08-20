#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <QVector>

class Polynomial
{
public:
    Polynomial(const QVector<double>& coeffs);
    double evaluate(double x) const;

private:
    QVector<double> coefficients;
};


#endif // POLYNOMIAL_H
