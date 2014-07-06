#include "neuralsample.h"

NeuralSample::NeuralSample() {

}


void NeuralSample::Push(QVector<double> data, QVector<int> target) {
    _datas.push_back(data);
    _targets.push_back(target);
}


void NeuralSample::Clear() {
    _datas.clear();
    _targets.clear();
}


int NeuralSample::GetSampleSize() const {
    return _datas.size();
}


NeuralNetworkExample NeuralSample::GetExample(int index) {
    if (index >= 0 && index <= _datas.size())
        return NeuralNetworkExample(_datas.at(index), _targets.at(index));
    else
        return NeuralNetworkExample();
}


NeuralNetworkExample NeuralSample::operator [](int index) {
    return GetExample(index);
}
