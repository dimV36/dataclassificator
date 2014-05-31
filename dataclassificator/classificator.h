#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "tablecolumnchooser.h"
#include "neuronexample.h"

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

private slots:
    void on__action_open_sample_triggered();

private:
    Ui::Classificator *_ui;
    int _index_x;
    int _index_y;
    QVector<NeuronExample> _teach_sample;
    QMap<QString, int> _class_map;
};

#endif // CLASSIFICATOR_H
