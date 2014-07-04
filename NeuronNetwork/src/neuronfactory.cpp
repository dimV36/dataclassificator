#include "neuronfactory.h"

NeuronFactory::NeuronFactory(){

}


NeuronFactory::~NeuronFactory(){

}


PerceptronNeuronFactory::PerceptronNeuronFactory() {

}


PerceptronNeuronFactory::~PerceptronNeuronFactory() {

}


PerceptronNeuronFactory::CreateInputNeuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function) {
    return new Neuron (neurons_link_to, function);
}


PerceptronNeuronFactory::CreateOutputNeuron(NetworkFunction *function) {
    return new OutputLayerNeuron(new Neuron(function));
}


PerceptronNeuronFactory::CreateHiddenNeuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function) {
    return new HiddenLayerNeuron(new Neuron(neurons_link_to, function));
}
