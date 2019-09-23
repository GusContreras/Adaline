#include "adaline.h"
#include "point.h"
#include <QDebug>
#include <QtMath>

const double euler = 2.71828182845;

Adaline::Adaline()
{

}

Adaline::Adaline(int size)
{
    for(int i = 0; i < size; i++)
    {
        weights.append(Gen.bounded(10.0) - 5.0);
    }
}

int Adaline::functionZ(QVector<double> x)
{
    double test = 0.0;

    for(int i = 0; i < x.length(); i++)
    {
        test += x[i] * weights[i];
    }

    if(test > 0.0)
    {
        return 1;
    }
    return 0;
}

void Adaline::rand()
{
    for(int i = 0; i < weights.length(); i++)
    {
        weights[i] = Gen.bounded(10.0) - 5.0;
    }
}

void Adaline::updateA(QVector<double> x, double factor, double error)
{
    double z = functionS(x);
    z = z * (1 - z);

    for(int i = 0; i < x.length(); i++)
    {
        weights[i] += x[i] * factor * error * z;
    }

}

double Adaline::functionS(QVector<double> x)
{
    double sumz = 0.0;

    for(int i = 0; i < x.length(); i++)
    {
        sumz += x[i] * weights[i];
    }

    double sig =  (1.0/(1.0 + qPow(euler,sumz*(-1.0))));
    return sig;
}
