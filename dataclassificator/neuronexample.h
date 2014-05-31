#ifndef NEURONEXAMPLE_H
#define NEURONEXAMPLE_H

class NeuronExample
{
private:
    int _class_number;
    double _x;
    double _y;

public:
    NeuronExample();
    NeuronExample(int class_number, double x, double y);
    NeuronExample(const NeuronExample &example);

    int get_class_number() const;
    double get_x() const;
    double get_y() const;

    void set_class_number(int class_number);
    void set_x(double x);
    void set_y(double y);
};

#endif // NEURONEXAMPLE_H
