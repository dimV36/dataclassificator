#ifndef TRAINALGORITHM_H_
#define TRAINALGORITHM_H_

#include <QVector>
#include <QDebug>
#include <time.h>
#include "neuralnetwork.h"

class NeuralNetwork;

class TrainAlgorithm {
protected:
public:
    virtual ~TrainAlgorithm();
    virtual double Train(const QVector<double> &data, const QVector<int> &target) = 0;
    virtual void WeightsInitialization() = 0;
};


class Hebb : public TrainAlgorithm {
protected:
    NeuralNetwork *_neural_network;
public:
    Hebb(NeuralNetwork *neural_network);
    virtual ~Hebb();
    virtual double Train(const QVector<double> &data, const QVector<int> &target);
    virtual void WeightsInitialization();
};


class Backpropagation : public TrainAlgorithm {
protected:
    NeuralNetwork *_neural_network;
public:
    Backpropagation(NeuralNetwork *neural_network);
    virtual ~Backpropagation();
    virtual double Train(const QVector<double> &data, const QVector<int> &target);
    virtual void WeightsInitialization();
protected:
    void NguyenWidrowWeightsInitialization();
    void CommonInitialization();
};




#endif /* TRAINALGORITHM_H_ */
