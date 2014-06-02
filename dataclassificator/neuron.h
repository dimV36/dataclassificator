#ifndef NEURON_H
#define NEURON_H

#include <QVector>

/**
* Нейрон с пороговой функцией
*/
class Neuron {
private:
    QVector<double> _weights;
    int _step; // Значение порога

private:
    double GetSum(QVector<double> input);
    int Activator(double sum);

public:
    Neuron();
    Neuron(int count);
    Neuron(const Neuron &neuron);
    ~Neuron();

    int Transfer(QVector<double> x);
    void InitWeights(int step);
    void ChangeWeights(int speed, double delta, QVector<double> x);

    Neuron operator = (Neuron &neuron);
    Neuron operator = (const Neuron &neuron);
    bool operator == (const Neuron &neuron);
    bool operator != (const Neuron &neuron);
};

#endif // NEURON_H

