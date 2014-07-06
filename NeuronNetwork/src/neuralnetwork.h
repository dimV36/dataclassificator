#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "neuronfactory.h"
#include "trainalgorithm.h"
#include "networkfunction.h"
#include <QDebug>

class TrainAlgorithm;

class NeuralNetwork {
    friend class Hebb;
    friend class Backpropagation;

protected:
    NeuronFactory *_neuron_factory;							/* Отвечает за создание нейронов */
    TrainAlgorithm *_training_algorithm;                    /* Отвечает за обучение сети */
    QVector<QVector<Neuron*> > 	_layers;					/* Слои нейронов */
    QVector<Neuron*> _bias_layer;					        /* Слой смещения */
    int _inputs;                                            /* Число входов сети */
    int _outputs;                                           /* Число выходов сети */
    int _hidden;			                                /* Число скрытых слоёв */
    double _mean_squared_error;				                /* Среднеквадратическая ошибка при обучении */
    double _min_mean_squared_error;					        /* Наибольшая среднеквадратическая ошибка для остановки обучения сети */

public:
    NeuralNetwork(int inputs, int outputs, int number_of_hidden_layers = 0, int number_of_neurons_in_hidden_layers = 0, ActivationFunction function = SigmoidFunction);
    ~NeuralNetwork();

    void set_algorithm(TrainAlgorithm *algorithm);
    void set_neuron_factory(NeuronFactory *factory);
    void set_min_mean_squared_error(double error);

    int get_inputs() const;
    int get_outputs() const;
    QVector<QVector<Neuron*> > get_layers() const;

    double get_min_mean_squared_error() const;
    bool Train(QVector<QVector<double> > &data, QVector<QVector<int> > &target);
    QVector<int> NetResponse(QVector<double> &data);
    void ShowNetworkState();

protected:
    QVector<Neuron *> GetLayer(int index) const;
    int size() const;
    QVector<Neuron *> GetOutputLayer() const;
    QVector<Neuron *> GetInputLayer() const;
    QVector<Neuron *> GetBiasLayer() const;
    void UpdateWeights();
    void ResetCharges();
    void AddMSE(double value);
    double get_mean_squared_error() const;
    void ResetMSE();
};




#endif /* NEURALNETWORK_H_ */
