#ifndef NETWORKFUNCTION_H_
#define NETWORKFUNCTION_H_

#include <QtMath>

/* Базовый класс для всех функций активации */
class NetworkFunction {
public:
    NetworkFunction();
    virtual ~NetworkFunction();
    /* Функция */
    virtual double Process(double value) = 0;
    /* Производная */
    virtual double Derivative(double value) = 0;
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
    virtual double Process(double value); /*{ return ( 1 / ( 1 + exp( -inParam ) ) ); }*/
    virtual double Derivative(double value); /*{ return ( this->Process(inParam)*(1 - this->Process(inParam)) );};*/
};

/* Класс биполярного сигмоида */
class BipolarSigmoid : public NetworkFunction {
public:
    BipolarSigmoid();
    virtual ~BipolarSigmoid();
    virtual double Process(double value); /*{ return ( 2 / ( 1 + exp( -inParam ) ) - 1 ) ;};*/
    virtual double Derivative(double value); /*{ return ( 0.5 * ( 1 + this->Process( inParam ) ) * ( 1 - this->Process( inParam ) ) ); };*/
};

#endif /* NETWORKFUNCTION_H_ */


