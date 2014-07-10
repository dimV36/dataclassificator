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
double NetworkFunction::Process(double) {
    return 0.0;
}


/**
 * Возвращает производную функции по параметру value
 * @brief NetworkFunction::Derivative
 * @param value
 * @return
 */
double NetworkFunction::Derivative(double) {
    return 0.0;
}

/**************************** Реализация методов класса Linear ****************************/
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


/**************************** Реализация методов класса Sigmoid ****************************/
Sigmoid::Sigmoid() {

}


Sigmoid::~Sigmoid() {

}


double Sigmoid::Process(double value) {
    return (1 / (1 + qExp(-value)));
}


double Sigmoid::Derivative(double value) {
    return Process(value) * (1 - Process(value));
}


/**************************** Реализация методов класса BipolarSigmoid ****************************/


BipolarSigmoid::BipolarSigmoid() {

}


BipolarSigmoid::~BipolarSigmoid() {

}


double BipolarSigmoid::Process(double value) {
    return (2 / (1 + qExp(-value)) - 1);
}


double BipolarSigmoid::Derivative(double value) {
    return (1 - qPow(Process(value), 2)) / 2;
}
