#include "neuronexample.h"


NeuronExample::NeuronExample() {
    _class_number = 0;
    _x = 0;
    _y = 0;
}


NeuronExample::NeuronExample(int class_number, double x, double y) {
    _class_number = class_number;
    _x = x;
    _y = y;
}


NeuronExample::NeuronExample(const NeuronExample &example) {
   _class_number = example._class_number;
    _x = example._x;
    _y = example._y;
}


int NeuronExample::get_class_number() const {
    return _class_number;
}


double NeuronExample::get_x() const {
    return _x;
}


double NeuronExample::get_y() const {
    return _y;
}


void NeuronExample::set_class_number(int class_number) {
    _class_number = class_number;
}


void NeuronExample::set_x(double x) {
    _x = x;
}


void NeuronExample::set_y(double y) {
    _y = y;
}
