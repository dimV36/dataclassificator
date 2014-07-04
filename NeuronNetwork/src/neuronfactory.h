#ifndef NEURONFACTORY_H_
#define NEURONFACTORY_H_

#include "neuron.h"

class NeuronFactory {
public:
    NeuronFactory();
    virtual ~NeuronFactory();
    virtual Neuron* CreateInputNeuron(QVector<Neuron*>& neurons_link_to, NetworkFunction *function) = 0;
    virtual Neuron* CreateOutputNeuron(NetworkFunction *function) = 0;
    virtual Neuron* CreateHiddenNeuron(QVector<Neuron*>& neurons_link_to, NetworkFunction *function) = 0;

};


class PerceptronNeuronFactory : public NeuronFactory {
public:
    PerceptronNeuronFactory();
    virtual	~PerceptronNeuronFactory();
    virtual Neuron* CreateInputNeuron(QVector<Neuron*>& neurons_link_to, NetworkFunction *function);
    virtual Neuron* CreateOutputNeuron(NetworkFunction *function);
    virtual Neuron* CreateHiddenNeuron(QVector<Neuron*>& neurons_link_to, NetworkFunction *function);
};


#endif /* NEURONFACTORY_H_ */
