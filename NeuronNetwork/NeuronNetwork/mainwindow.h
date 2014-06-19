#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGVCore/QGVScene.h>
#include <QGVCore/QGVNode.h>
#include <QGVCore/QGVEdge.h>
#include <QGVCore/QGVSubGraph.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawGraph();

private slots:
    void nodeContextMenu(QGVNode* node);
    void nodeDoubleClick(QGVNode* node);

private:
    Ui::MainWindow *_ui;
    QGVScene *_scene;
};

#endif // MAINWINDOW_H
