#include "polynomial.h"
#include "qcontainerfwd.h"

Polynomial:: Polynomial(const QVector<double>& coeffs) : coefficients(coeffs)
{

}

double Polynomial::evaluate(double x) const
{
    double result = 0.0;
    for (int i = 0; i < coefficients.size(); ++i)
    {
        result = result * x + coefficients[i];
    }
    return result;
}
