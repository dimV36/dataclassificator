#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include <QGVCore/QGVScene.h>
#include <QGVCore/QGVNode.h>
#include <QGVCore/QGVEdge.h>

#include "neuronnetworksettingsdialog.h"

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
    QVector<QGVNode*> GetLayout(int index) const;
    void AddEdges(QGVNode *node, int layout);
    void CreateInputNode();
    void CreateOutputNode();

signals:
    void SignalNetworkSettingsChanged();

private slots:
    void SlotDrawGraph();

    void on__action_open_triggered();
    void on__action_teach_triggered();
    void on__action_classificate_triggered();
    void on__action_network_settings_triggered();

private:
    Ui::MainWindow *_ui;
    QGVScene *_scene;
    QVector<QVector<QGVNode*> > _nodes;

    int _input;
    int _output;
    int _layout_count;
    int _neurons_in_layout;
};

#endif // MAINWINDOW_H
