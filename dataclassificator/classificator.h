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

private slots:
    void on__action_open_sample_triggered();
    void on__action_teach_triggered();
    void on__action_classificate_triggered();

private:
    Ui::Classificator *_ui;
    int _index_x;
    int _index_y;

    QVector<NeuronExample> _teach_sample;
    Perceptron _perceptron;
    QMap<QString, int> _class_map;
};

#endif // CLASSIFICATOR_H
