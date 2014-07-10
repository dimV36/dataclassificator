#include "classificatordialog.h"
#include "ui_classificatordialog.h"

ClassificatorDialog::ClassificatorDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ClassificatorDialog) {
    _ui -> setupUi(this);
}


ClassificatorDialog::~ClassificatorDialog() {
    delete _ui;
}
