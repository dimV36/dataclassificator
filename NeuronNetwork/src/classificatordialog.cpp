#include "classificatordialog.h"
#include "ui_classificatordialog.h"

#include <QDebug>

ClassificatorDialog::ClassificatorDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ClassificatorDialog) {
    _ui -> setupUi(this);

    _ui -> _table_statistic -> setHidden(true);
    connect(_ui -> _button_statistic, SIGNAL(clicked()), this, SLOT(SlotSetStatisticHidden()));

    _ui -> _edit_file_name -> setText(QDir::currentPath() + "/results.txt");
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
        QString status;
        if (pair.first == pair.second)
            status = "OK";
        else
            status = "Ошибка";
        _ui -> _table -> setItem(current_row, STATUS_SECTION, new QTableWidgetItem(status));
        UpdateMapStatistic(pair.first, status);
    }
    SetStatistic();
}


void ClassificatorDialog::SlotSetStatisticHidden() {
    bool is_hidden = _ui -> _table_statistic -> isHidden();
    _ui -> _table_statistic -> setHidden(!is_hidden);
}


void ClassificatorDialog::UpdateMapStatistic(QString class_name, QString status) {
    if (false == _class_counts.contains(class_name))
        _class_counts[class_name] = 1;
    else
        _class_counts[class_name] += 1;
    if (QString("OK") == status)
        _statistic_map[class_name] += 1;
}


void ClassificatorDialog::SetStatistic() {
    QStringList keys = _class_counts.keys();
    _ui -> _table_statistic -> setRowCount(keys.size());
    _ui -> _table_statistic -> setColumnCount(keys.size());
    _ui -> _table_statistic -> setVerticalHeaderLabels(keys);
    _ui -> _table_statistic -> setHorizontalHeaderLabels(keys);
    _ui -> _table_statistic -> verticalHeader() -> setVisible(true);
    _ui -> _table_statistic -> horizontalHeader() -> setVisible(true);
    for (int i = 0; i < keys.size(); i++)
        _ui -> _table_statistic -> setItem(i, i, new QTableWidgetItem(QString::number(( (double) _statistic_map[keys[i]] / (double) _class_counts[keys[i]]) * 100, 'g', 3)));
}


QStringList ClassificatorDialog::get_statistic() const {
    QStringList result;
    QStringList keys = _class_counts.keys();
    int rows = _ui -> _table_statistic -> rowCount();
    for (int i = 0; i < rows; i++) {
        QString row = keys[i] + "\t" + _ui -> _table_statistic -> item(i, i) -> text() + "\n";
        result.push_back(row);
    }
    return result;
}


void ClassificatorDialog::on__button_change_file_name_clicked() {
    QString file_name = QFileDialog::getSaveFileName(this, tr("Выбрать путь для сохранения"),
                                                     QDir::currentPath());
    _ui -> _edit_file_name -> setText(file_name);
}


QString ClassificatorDialog::get_file_name() const {
    return _ui -> _edit_file_name -> text();
}
