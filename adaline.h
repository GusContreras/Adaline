#ifndef ADALINE_H
#define ADALINE_H
#include <QRandomGenerator>
#include "point.h"

class Adaline
{
public:
    Adaline();
    Adaline(int size);
    QVector<double> weights;
    QRandomGenerator Gen;
    int functionZ(QVector<double> x);
    void rand();
    void updateA(QVector<double> x, double factor, double error);
    double functionS(QVector<double> x);
};

#endif // ADALINE_H
