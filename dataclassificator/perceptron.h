#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "neuron.h"
#include "neuronexample.h"

class Perceptron
{
private:
    int _output;                // Количество выходов
    QVector<Neuron *> _neurons;   // Вектор нейронов

public:
    Perceptron();
    Perceptron(int count, int output);
    Perceptron(const Perceptron &perceptron);
    ~Perceptron();

    QVector<int> Recognize(QVector<double> x);
    void InitWeights(int weight);
    void Teach(QVector<double> x, QVector<int> y, int speed);
    QVector<int> MakeOutputVector(const NeuronExample &example);
    int GetClass(QVector<double> x);

    Perceptron operator = (Perceptron &perceptron);
    Perceptron operator = (const Perceptron &perceptron);
    bool operator == (const Perceptron &perceptron);
    bool operator != (const Perceptron &perceptron);
};

#endif // PERCEPTRON_H
