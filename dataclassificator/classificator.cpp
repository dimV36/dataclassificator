#include "classificator.h"
#include "ui_classificator.h"

#include <QDebug>

Classificator::Classificator(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Classificator) {
    _ui -> setupUi(this);
}


Classificator::~Classificator() {
    delete _ui;
}


void Classificator::on__action_open_sample_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с тестовой выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    CreateTeachSample(file_name);
}


void Classificator::CreateTeachSample(QString file_name) {
    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    QStringList headers = QString(file.readLine()).split('\t');
    headers.pop_front();

    QStringList choosen_data;
    TableColumnChooser chooser;
    chooser.set_headers(headers);
    if (chooser.exec() == QDialog::Accepted) {
        choosen_data = chooser.get_headers();
    }
    _index_x = headers.indexOf(choosen_data.at(0));
    _index_y = headers.indexOf(choosen_data.at(1));

    while(false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        QString class_name = row_list.at(0);
        double x = row_list.at(_index_x).toDouble();
        double y = row_list.at(_index_y).toDouble();
        if (false == _class_map.contains(class_name)) {
            if (true == _class_map.isEmpty())
                _class_map.insert(class_name, 1);
            else
                _class_map.insert(class_name, _class_map.size() + 1);
        }
        NeuronExample example(_class_map.value(class_name), x, y);
        _teach_sample.push_front(example);
    }
    file.close();
}
