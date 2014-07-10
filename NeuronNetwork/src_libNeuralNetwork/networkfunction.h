#ifndef NETWORKFUNCTION_H_
#define NETWORKFUNCTION_H_

#include <QtMath>

enum ActivationFunction {LinearFunction, SigmoidFunction, BipolarSigmoidFunction};

/* Базовый класс для всех функций активации */
class NetworkFunction {
public:
    NetworkFunction();
    virtual ~NetworkFunction();
    /* Функция */
    virtual double Process(double);
    /* Производная */
    virtual double Derivative(double);
};


/* Класс линейной функции активации */
class Linear : public NetworkFunction {
public:
    Linear();
    virtual ~Linear();
    virtual double Process(double value);
    virtual double Derivative(double);
};


/* Класс однополярного сигмоида */
class Sigmoid : public NetworkFunction {
public:
    Sigmoid();
    virtual ~Sigmoid();
    virtual double Process(double value);
    virtual double Derivative(double value);
};

/* Класс биполярного сигмоида */
class BipolarSigmoid : public NetworkFunction {
public:
    BipolarSigmoid();
    virtual ~BipolarSigmoid();
    virtual double Process(double value);
    virtual double Derivative(double value);
};

#endif /* NETWORKFUNCTION_H_ */


