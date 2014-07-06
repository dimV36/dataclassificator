#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>

#include <QGVScene.h>
#include <QGVNode.h>
#include <QGVEdge.h>

#include "neuronnetworksettingsdialog.h"
#include "neuralsample.h"
#include "tablecolumnchooser.h"
#include "neuralnetwork.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void CreateTeachSample(QString file_name);
    void CreateNetwork();
    void ShakeExamples();
    QVector<QGVNode*> GetLayout(int index) const;
    void AddEdges(QGVNode *node, int layout);
    void CreateInputNode();
    void CreateOutputNode();

    QVector<int> ConvertClassToVector(int class_number);

signals:
    void SignalNetworkSettingsChanged();

private slots:
    void SlotDrawGraph();

    void on__action_open_sample_triggered();
    void on__action_teach_triggered();
    void on__action_classificate_triggered();
    void on__action_network_settings_triggered();

private:
    Ui::MainWindow *_ui;
    /* Сцена, на которой отрисовывается визуальное представление сети */
    QGVScene *_scene;
    /* Сами узлы сети */
    QVector<QVector<QGVNode*> > _nodes;

    /* Параметры сети, которые пользователь вводит */
    int _input;                   // Количество входов
    int _output;                  // Количество выходов
    int _layout_count;            // Количество слоёв
    int _neurons_in_layout;       // Количество нейронов в слое
    ActivationFunction _function; // Значение активационной функции в слоях

    QList<int> _choosen_column; // Список со значениями выбранных столбцов

    NeuralSample _teach_sample;       // Выборка обучающих примеров
    NeuralNetwork *_network;                    // Нейронная сеть
    QMap<QString, int> _class_map;              // Карта соответствия имени номеру класса
};

#endif // MAINWINDOW_H
