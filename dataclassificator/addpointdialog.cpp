#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AddPointDialog) {
    _ui -> setupUi(this);
}


AddPointDialog::~AddPointDialog() {
    delete _ui;
}


double AddPointDialog::get_x() const {
    return _ui -> _box_x -> value();
}


double AddPointDialog::get_y() const {
    return _ui -> _box_y -> value();
}
