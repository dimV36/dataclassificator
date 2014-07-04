#include "networkfunction.h"

/**
 * Конструктор по умолчанию
 * @brief NetworkFunction::NetworkFunction
 */
NetworkFunction::NetworkFunction() {

}


/**
 * Деструктор
 * @brief NetworkFunction::~NetworkFunction
 */
NetworkFunction::~NetworkFunction() {

}


/**
 * Возвращает значение функции по параметру value
 * @brief NetworkFunction::Process
 * @param value
 * @return
 */
double NetworkFunction::Process(double value) {

}


/**
 * Возвращает производную функции по параметру value
 * @brief NetworkFunction::Derivative
 * @param value
 * @return
 */
double NetworkFunction::Derivative(double value) {

}

/**************************** Определение методов класса Linear ****************************/
Linear::Linear() {

}


Linear::~Linear() {

}


double Linear::Process(double value) {
    return value;
}


double Linear::Derivative(double) {
    return 1; // Точно?
}


/**************************** Определение методов класса Sigmoid ****************************/
Sigmoid::Sigmoid() {

}


Sigmoid::~Sigmoid() {

}


Sigmoid::Process(double value) {
    return (1 / (1 + exp(-value)));
}


Sigmoid::Derivative(double value) {
    return Process(value) * (1 - Process(value));
}


/**************************** Определение методов класса BipolarSigmoid ****************************/


BipolarSigmoid::BipolarSigmoid() {

}


BipolarSigmoid::~BipolarSigmoid() {

}


BipolarSigmoid::Process(double value) {
    return (2 / (1 + exp(-value)) - 1);
}


BipolarSigmoid::Derivative(double value) {
    return (1 - qPow(Process(value), 2)) / 2;
}
