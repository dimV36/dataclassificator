#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <QMainWindow>

namespace Ui {
class Classificator;
}

class Classificator : public QMainWindow {
    Q_OBJECT

public:
    explicit Classificator(QWidget *parent = 0);
    ~Classificator();

private:
    Ui::Classificator *_ui;
};

#endif // CLASSIFICATOR_H
