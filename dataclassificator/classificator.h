#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "tablecolumnchooser.h"

namespace Ui {
class Classificator;
}

class Classificator : public QMainWindow {
    Q_OBJECT

public:
    explicit Classificator(QWidget *parent = 0);
    ~Classificator();

private slots:
    void on__action_open_sample_triggered();

private:
    Ui::Classificator *_ui;
};

#endif // CLASSIFICATOR_H
