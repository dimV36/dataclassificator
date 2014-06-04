#include "teachprocess.h"
#include "ui_teachprocess.h"

TeachProcess::TeachProcess(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::TeachProcess) {
    _ui -> setupUi(this);
    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));
}


TeachProcess::~TeachProcess() {
    delete _ui;
}


int TeachProcess::get_count() const {
    return _ui -> _box_count -> value();
}


int TeachProcess::get_speed() const {
    return _ui -> _speed_box -> value();
}
