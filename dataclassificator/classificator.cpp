#include "classificator.h"
#include "ui_classificator.h"

Classificator::Classificator(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Classificator) {
    _ui -> setupUi(this);
}


Classificator::~Classificator() {
    delete _ui;
}
