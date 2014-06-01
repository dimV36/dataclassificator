#ifndef NEURON_H
#define NEURON_H

#include <QTime>
#include <QVector>
#include "qmath.h"

/**
* Нейрон с пороговой функцией
*/
class Neuron {
private:
    QVector<double> _weights;
    int _step = 50; // Значение порога

private:
    double GetSum(double *input);
    int Activator(double sum);

public:
    Neuron();
    Neuron(int count);
    Neuron(const Neuron &neuron);
    ~Neuron();

    int Transfer(double *weight);
    void InitWeights(int step);
    void ChangeWeights(int speed, double delta, double *x);

    Neuron operator= (Neuron neuron);
    bool operator== (Neuron neuron);
};

#endif // NEURON_H

