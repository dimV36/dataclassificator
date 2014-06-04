#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include "qmath.h"

#include "tablecolumnchooser.h"
#include "neuronexample.h"
#include "neuron.h"
#include "perceptron.h"
#include "teachprocess.h"
#include "addpointdialog.h"

namespace Ui {
class Classificator;
}

class Classificator : public QMainWindow {
    Q_OBJECT

public:
    explicit Classificator(QWidget *parent = 0);
    ~Classificator();

private:
    void CreateTeachSample(QString file_name);
    void ShakeExamples();
    QPair<int,int> UpdateRange(QPair<int,int> range, double value);

private slots:
    void on__action_open_sample_triggered();
    void on__action_teach_triggered();
    void on__action_classificate_triggered();

    void on__action_add_point_triggered();

private:
    Ui::Classificator *_ui;
    /* Переменные отвечают за столбцы выбранных пользователем данных */
    int _index_x;
    int _index_y;

    QVector<NeuronExample> _teach_sample;       // Выборка обучающих примеров
    Perceptron _perceptron;                     // Персептрон
    QMap<QString, int> _class_map;              // Карта соответствия имени номеру класса
    QPair<int,int> _xrange;                     // Вспомогательные переменные,
                                                // необходимы для установки минимального и максимального значения осей на графике
    QPair<int,int> _yrange;
};

#endif // CLASSIFICATOR_H
