#include "neuronexample.h"


NeuronExample::NeuronExample() {
    _data = QVector<double>();
    _class_name = 0;
}


NeuronExample::NeuronExample(QVector<double> data, int class_name) {
    _data = data;
    _class_name = class_name;
}


NeuronExample::NeuronExample(const NeuronExample &example) {
   _data = example._data;
   _class_name = example._class_name;
}


QVector<double> NeuronExample::get_data() const {
    return _data;
}


int NeuronExample::get_class_name() const {
    return _class_name;
}


void NeuronExample::set_data(QVector<double> data) {
    _data = data;
}


void NeuronExample::set_class_name(int class_name) {
    _class_name = class_name;
}
