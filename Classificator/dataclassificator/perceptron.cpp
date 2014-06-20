#include "perceptron.h"

    /**
     * Конструктор по умолчанию
     * @brief Perceptron::Perceptron
     */
    Perceptron::Perceptron() {
        _output = 1;
        _neurons.push_back(new Neuron());
    }


    /**
     * Конструктор
     * @param count - число нейронов
     * @param output - число входов каждого нейрона скрытого слоя
     */
    Perceptron::Perceptron(int count, int output) {
        _output = output;
        _neurons = QVector<Neuron *>();
        for (int i = 0; i < count; i++)
            _neurons.push_back(new Neuron(output));
    }


    /**
     * Копирующий конструктор
     * @brief Perceptron::Perceptron
     * @param perceptron
     */
    Perceptron::Perceptron(const Perceptron &perceptron) {
        _output = perceptron._output;
        _neurons = perceptron._neurons;
    }


    /**
     * Деструктор
     * @brief Perceptron::~Perceptron
     */
    Perceptron::~Perceptron() {

    }

    /**
     * Распознавание образа
     * @param x - входной вектор
     * @return - выходной образ
     */
    QVector<int> Perceptron::Recognize(QVector<double> x) {
        QVector<int> result = QVector<int>(_neurons.size());

        for (int i = 0; i < _neurons.size(); i++)
            result[i] = _neurons[i] -> Transfer(x);
        return result;
    }

    /**
     * Инициализация начальных весов
     * малым случайным значением
     */
    void Perceptron::InitWeights(int weight) {
        for (int i = 0; i < _neurons.size(); i++)
            _neurons[i] -> InitWeights(weight);
    }


    /**
     * Обучение перцептрона
     * @param x - входной вектор
     * @param y - правильный выходной вектор
     */
    void Perceptron::Teach(QVector<double> x, QVector<int> y, int speed) {
        int delta;
        QVector<int> t = Recognize(x);
        while (false == (t == y)) {
            // подстройка весов каждого нейрона
            for (int i = 0; i < _neurons.size(); i++) {
                delta = y[i] - t[i];
                _neurons[i] -> ChangeWeights(speed, delta, x);
            }
            t = Recognize(x);
        }
    }

    /**
     * Создать бинарный вектор выхода по входному примеру
     * @brief Perceptron::MakeOutputVector
     * @param example
     * @return
     */
    QVector<int> Perceptron::MakeOutputVector(const NeuronExample &example) {
        QVector<int> result(_neurons.size());
        int class_name = example.get_class_name();
        for (int i = 0; i < result.size(); i++) {
            if (class_name - 1 == i)
                result[i] = 1;
            else
                result[i] = 0;
        }
        return result;
    }


    int Perceptron::GetClass(QVector<double> x) {
        QVector<int> reaction = Recognize(x);
        for (int i = 0; i < reaction.size(); i++) {
            if (reaction[i] == 1)
                return (i + 1);
        }
        return 0;
    }


    /**
     * Оператор присваивания
     * @brief Perceptron::operator =
     * @param perceptron
     * @return
     */
    Perceptron Perceptron::operator = (Perceptron &perceptron) {
        if (*this != perceptron) {
            _output = perceptron._output;
            _neurons = perceptron._neurons;
        }
        return *this;
    }


    Perceptron Perceptron::operator = (const Perceptron &perceptron) {
        if (*this != perceptron) {
            _output = perceptron._output;
            _neurons = perceptron._neurons;
        }
        return *this;
    }

    /**
     * Оператор сравнения на равенство
     * @brief Perceptron::operator ==
     * @param perceptron
     * @return
     */
    bool Perceptron::operator == (const Perceptron &perceptron) {
        if (_output == perceptron._output && _neurons == perceptron._neurons)
            return true;
        else
            return false;
    }


    bool Perceptron::operator != (const Perceptron &perceptron) {
        return !(*this == perceptron);
    }
