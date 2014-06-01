#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "neuron.h"

class Perceptron
{
private:
    int _input;
    int _output;
    QVector<Neuron> _neurons;

public:
    Perceptron(int input, int output);
};

#endif // PERCEPTRON_H
