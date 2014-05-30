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
    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    QStringList headers = QString(file.readLine()).split('\t');

    TableColumnChooser chooser;
    chooser.set_headers(headers);
    if (chooser.exec() == QDialog::Accepted) {
        qDebug() << "ok";
    }
}
