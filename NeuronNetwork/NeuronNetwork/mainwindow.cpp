#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow) {
    _ui -> setupUi(this);

    /* Перерисовка графа по измению параметров сети */
    connect(this, SIGNAL(SignalNetworkSettingsChanged()), this, SLOT(SlotDrawGraph()));

    _scene = new QGVScene(QString());
    _ui -> _view -> setScene(_scene);

    _input = _output = _layout_count = _neurons_in_layout = 1;
}


MainWindow::~MainWindow() {
    delete _ui;
}


QVector<QGVNode*> MainWindow::GetLayout(int index) const {
    QVector<QGVNode*> result;
    for (int i = 0; i < _neurons_in_layout; i++)
        result.push_back(_nodes[index][i]);
    return result;
}


void MainWindow::AddEdges(QGVNode *node, int layout) {
    QVector<QGVNode*> next_layout = GetLayout(layout + 1);
    for (int i = 0; i < next_layout.size(); i++)
        _scene -> addEdge(node, next_layout[i]);
}


void MainWindow::CreateInputNode() {
    QString input_label;
    for (int i = 0; i < _input; i++)
        input_label += "x" + QString::number(i + 1) + "\n";
    input_label.chop(1);
    QGVNode *input = _scene -> addNode(input_label);
    input -> setAttribute("shape", "box");
    AddEdges(input, -1);
}


void MainWindow::CreateOutputNode() {
    QString output_label;
    for (int i = 0; i < _output; i++)
        output_label += "y" + QString::number(i + 1) + "\n";
    output_label.chop(1);
    QGVNode *output = _scene -> addNode(output_label);
    output -> setAttribute("shape", "box");
    QVector<QGVNode*> last_layer = GetLayout(_layout_count - 1);
    for (int i = 0; i < last_layer.size(); i++)
        _scene -> addEdge(last_layer[i], output);
}


void MainWindow::SlotDrawGraph() {
    _scene -> clear();
    _nodes.clear();

    _scene -> setGraphAttribute("splines", "spline");
    _scene -> setGraphAttribute("rankdir", "LR");
    _scene -> setGraphAttribute("nodesep", "1.0");

    _scene -> setNodeAttribute("shape", "circle");
    _scene -> setNodeAttribute("style", "filled");
    _scene -> setNodeAttribute("fillcolor", "white");
    _scene -> setNodeAttribute("height", "1.2");


    int number = 1;
    for (int i = 0; i < _layout_count; i++) {
        QVector<QGVNode *> layer;
        for (int j = 0; j < _neurons_in_layout; j++) {
            QGVNode *node = _scene -> addNode(QString::number(number));
            layer.push_back(node);
            number++;
        }
        _nodes.push_back(layer);
    }

    CreateInputNode();

    for (int i = 0; i < _layout_count; i++)
        for (int j = 0; j < _neurons_in_layout; j++) {
        QGVNode *node = _nodes[i][j];
        if (i + 1 != _layout_count)
            AddEdges(node, i);
    }

    CreateOutputNode();

    //Layout scene
    _scene -> applyLayout();

    //Fit in view
    _ui -> _view -> fitInView(_scene -> sceneRect(), Qt::KeepAspectRatio);
}


void MainWindow::on__action_open_triggered() {

}


void MainWindow::on__action_teach_triggered() {

}


void MainWindow::on__action_classificate_triggered() {

}


void MainWindow::on__action_network_settings_triggered() {
    NeuronNetworkSettingsDialog dialog;
    dialog.set_input(_input);
    dialog.set_output(_output);
    dialog.set_layout_count(_layout_count);
    dialog.set_neurons_in_layout(_neurons_in_layout);
    if (dialog.exec() == QDialog::Accepted) {
        _input = dialog.get_input();
        _output = dialog.get_output();
        _layout_count = dialog.get_layout_count();
        _neurons_in_layout = dialog.get_neurons_in_layout();
        emit SignalNetworkSettingsChanged();
    }
}
