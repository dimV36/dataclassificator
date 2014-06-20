#ifndef NEURONEXAMPLE_H
#define NEURONEXAMPLE_H

#include <QVector>

class NeuronExample
{
private:
    QVector<double> _data;
    int _class_name;

public:
    NeuronExample();
    NeuronExample(QVector<double> data, int class_name);
    NeuronExample(const NeuronExample &example);

    QVector<double> get_data() const;
    int get_class_name() const;

    void set_data(QVector<double> data);
    void set_class_name(int class_name);
};

#endif // NEURONEXAMPLE_H
