#include "classificator.h"
#include "ui_classificator.h"

#include <QDebug>

Classificator::Classificator(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Classificator) {
    _ui -> setupUi(this);

    _ui -> _action_teach -> setEnabled(false);
    _ui -> _action_classificate -> setEnabled(false);
}


Classificator::~Classificator() {
    delete _ui;
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
        QVector<double> vector;
        vector.push_back(x);
        vector.push_back(y);
        NeuronExample example(vector, _class_map.value(class_name));
        _teach_sample.push_back(example);
    }
    ShakeExamples();
    file.close();
}


void Classificator::ShakeExamples() {
    for (int i = 0; i < _teach_sample.size(); i++) {
        NeuronExample temp = _teach_sample[i];
        _teach_sample[i] = _teach_sample[qrand() % _teach_sample.size()];
        _teach_sample[qrand() % _teach_sample.size()] = temp;
    }
}


void Classificator::on__action_open_sample_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с обучающей выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    CreateTeachSample(file_name);
    _ui -> _action_teach -> setEnabled(true);
}


void Classificator::on__action_teach_triggered() {
    _perceptron = Perceptron(_class_map.size(), 2);
    int count = 200;
    while(count-- > 0) {
        for (int i = 0; i < _teach_sample.size(); i++) {
            QVector<double> x = _teach_sample[i].get_data();
            QVector<int> y = _perceptron.MakeOutputVector(_teach_sample[i]);
            _perceptron.Teach(x, y);
        }
    }
    _ui -> _action_classificate -> setEnabled(true);
}


void Classificator::on__action_classificate_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с тестовой выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));

    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла тестовой выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    while(false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        double x = row_list.at(_index_x).toDouble();
        double y = row_list.at(_index_y).toDouble();

        QVector<double> vector;
        vector.push_back(x);
        vector.push_back(y);

        qDebug() << _perceptron.Recognize(vector);
//        _ui -> widget -> graph(0) -> setData()
    }
    file.close();
}
