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


void ClassificatorDialog::set_data(QList<QPair<QString, QString> > data) {
    for (int i = 0; i < data.size(); i++) {
        QPair<QString, QString> pair = data[i];
        _ui -> _table -> setRowCount(_ui -> _table -> rowCount() + 1);
        int current_row = _ui -> _table -> rowCount() - 1;
        _ui -> _table -> setItem(current_row, CLASS_SECTION, new QTableWidgetItem(pair.first));
        _ui -> _table -> setItem(current_row, NETWORK_RESPONSE_SECTION, new QTableWidgetItem(pair.second));
        if (pair.first == pair.second)
            _ui -> _table -> setItem(current_row, STATUS_SECTION, new QTableWidgetItem("OK"));
        else
            _ui -> _table -> setItem(current_row, STATUS_SECTION, new QTableWidgetItem("Ошибка"));
    }
}
