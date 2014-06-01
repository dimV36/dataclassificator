#include "neuron.h"

/**
 * Конструктор по умолчанию
 * @brief Neuron::Neuron
 */
Neuron::Neuron() {
   _weights = QVector<double>();
}


/**
  Копирующий конструктор
 * @brief Neuron::Neuron
 * @param neuron
 */
Neuron::Neuron(const Neuron &neuron) {
    if (*this != neuron) {
        _weights = neuron._weights;
    }
}

/**
 * Конструктор нейрона с количеством входов count
 * @brief Neuron::Neuron
 * @param count
 */
Neuron::Neuron(int count) {
    qsrand(QTime::secTo(QTime::currentTime()));
    _weights = QVector<double>(count);
    for (int i = 0; i < _weights.size(); i++)
        _weights[i] = double (qrand() / RAND_MAX);
}

/**
 * Деструктор
 * @brief Neuron::~Neuron
 */
Neuron::~Neuron() {

}


/**
 * Иницилазиация весов случайными значениями
 * @brief Neuron::InitWeights
 * @param step
 */
void Neuron::InitWeights(int step) {
    for (int i = 0; i < _weights.size(); i++)
        _weights[i] = double(qrand() / RAND_MAX + step);
}


/**
 * Модификация весов синапсов для обучения
 * @param speed - скорость обучения
 * @param delta - разница между выходом нейрона и нужным выходом
 * @param x - входной вектор
 */
void Neuron::ChangeWeights(int speed, double delta, double *x) {
    for (int i = 0; i < _weights.size(); i++)
        _weights[i] += (double) speed * delta * x[i];
}


/**
 * Сумматор
 * @param x - входной вектор
 * @return - невзвешенная сумма result
 */
double Neuron::GetSum(double *input) {
    double result = 0;
    for (int i = 0; i < _weights.size(); i++)
        result += input[i] * _weights[i];
    return result;
}


/**
 * Нелинейный преобразователь или функция активации,
 * в данном случае - жесткая пороговая функция,
 * имеющая область значений {0;1}
 * @param nec - выход сумматора
 * @return
 */
int Neuron::Activator(double sum) {
    if (sum >= _step)
        return 1;
    else
        return 0;
}


/**
 * Передаточная функция
 * @param x - входной вектор
 * @return - выходное значение нейрона
 */
int Neuron::Transfer(double *x) {
    return Activator(GetSum(x));
}


/**
 * Оператор присваивания
 * @brief Neuron::operator =
 * @param neuron
 */
Neuron Neuron::operator= (Neuron neuron) {
    if (*this != neuron) {
        _weights = neuron._weights;
        _step = neuron._step;
    }
}


/**
 * Оператор сравнения на равенство
 * @brief Neuron::operator ==
 * @param neuron
 * @return
 */
bool Neuron::operator== (Neuron neuron) {
    if (_weights == neuron._weights && _step == neuron._step)
        return true;
    else
        return false;
}
