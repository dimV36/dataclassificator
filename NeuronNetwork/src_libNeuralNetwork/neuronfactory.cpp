#include "neuronfactory.h"

NeuronFactory::NeuronFactory(){

}


NeuronFactory::~NeuronFactory(){

}


PerceptronNeuronFactory::PerceptronNeuronFactory() {

}


PerceptronNeuronFactory::~PerceptronNeuronFactory() {

}


Neuron* PerceptronNeuronFactory::CreateInputNeuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function) {
    return new Neuron (neurons_link_to, function);
}


Neuron* PerceptronNeuronFactory::CreateOutputNeuron(NetworkFunction *function) {
    return new OutputLayerNeuron(new Neuron(function));
}


Neuron* PerceptronNeuronFactory::CreateHiddenNeuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function) {
    return new HiddenLayerNeuron(new Neuron(neurons_link_to, function));
}
