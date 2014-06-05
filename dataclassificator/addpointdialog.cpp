#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AddPointDialog) {
    _ui -> setupUi(this);
    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));

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
