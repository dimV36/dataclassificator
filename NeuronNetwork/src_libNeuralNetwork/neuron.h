#ifndef NEURON_H_
#define NEURON_H_

#include "neurallink.h"
#include "networkfunction.h"
#include <QVector>
#include <QDebug>

/* Скорость обучения */
const double LEARNING_RATE = 0.01;


class Neuron {
protected:
    NetworkFunction *_network_function;
    /* Входные связи */
    QVector<NeuralLink*> _input_links;
    /* Связи от нейронов */
    QVector<NeuralLink*> _links_to_neurons;
    /* Сумма весов */
    double _sum_of_charges;
public:
    Neuron();
    Neuron(NetworkFunction *function);
    Neuron(QVector<NeuralLink*> links_to_neurons, NetworkFunction *function);
    Neuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function);
    virtual ~Neuron();

    virtual QVector<NeuralLink *> get_links_to_neurons() const;
    virtual NeuralLink* at(const int index_of_neural_link);

    virtual void set_link_to_neuron(NeuralLink *link);

    virtual void Input(double input_data);
    virtual double Fire();
    virtual int	get_number_of_links() const;
    virtual double get_sum_of_charges() const;
    virtual void ResetSumOfCharges();
    virtual double Process();
    virtual double Process(double value);
    virtual double Derivative();

    virtual void set_input_link(NeuralLink *link);
    virtual QVector<NeuralLink*> get_input_links() const;

    virtual double PerformTrainingProcess(double);
    virtual void PerformWeightsUpdating();

    virtual void ShowNeuronState();

};


class OutputLayerNeuron : public Neuron {
protected:
    double _output_charge;
    Neuron *_neuron;

public:
    OutputLayerNeuron(Neuron *neuron);
    virtual ~OutputLayerNeuron();

    virtual QVector<NeuralLink*> get_links_to_neurons() const;
    virtual NeuralLink* at(int index);
    virtual void set_link_to_neuron(NeuralLink *link);
    virtual double get_sum_of_charges() const;

    virtual void ResetSumOfCharges();
    virtual void Input(double input_data);
    virtual double Fire();
    virtual int	 get_number_of_links() const;

    virtual double Process();
    virtual double Process(double value);

    virtual double Derivative();

    virtual void set_input_link(NeuralLink *link);
    virtual QVector<NeuralLink*> get_input_links() const;

    virtual double PerformTrainingProcess(double target);
    virtual void PerformWeightsUpdating();
    virtual void ShowNeuronState();
};



class HiddenLayerNeuron : public Neuron {
protected:
    Neuron *_neuron;
public:
    HiddenLayerNeuron(Neuron *neuron);
    virtual ~HiddenLayerNeuron();

    virtual QVector<NeuralLink*> get_links_to_neurons() const;
    virtual NeuralLink* at(int index);
    virtual void set_link_to_neuron(NeuralLink *link);
    virtual double get_sum_of_charges() const;

    virtual void ResetSumOfCharges();
    virtual void Input(double input_data);
    virtual double Fire();
    virtual int	 get_number_of_links() const;

    virtual double Process();
    virtual double Process(double value);

    virtual double Derivative();

    virtual void set_input_link(NeuralLink *link);
    virtual QVector<NeuralLink*> get_input_links() const;

    virtual double PerformTrainingProcess(double);
    virtual void PerformWeightsUpdating();
    virtual void ShowNeuronState();
};

#endif /* NEURON_H_ */
