#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/**
 * Конструктор класса
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow) {
    _ui -> setupUi(this);

    /* Перерисовка графа по измению параметров сети */
    connect(this, SIGNAL(SignalNetworkSettingsChanged()), this, SLOT(SlotDrawGraph()));

    /* Создание сцены, на которой отрисовывается визуализация сети */
    _scene = new QGVScene(QString());
    _ui -> _view -> setScene(_scene);

    _input = _output = _layout_count = _neurons_in_layout = 1;
}

/**
 * Деструктор класса
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete _ui;
}


/**
 * Создать тестовую выборку
 * @brief Classificator::CreateTeachSample
 * @param file_name
 */
void MainWindow::CreateTeachSample(QString file_name) {
    _teach_sample.clear();
    _class_map.clear();
    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    /* Получить все возможные заголовки таблицы */
    QStringList headers = QString(file.readLine()).split('\t');
    /* Так как первый столбец содержит имя класса, исключаем из списка */
    headers.pop_front();

    /* Создаём диалоговое окно, позволяющее пользователю выбрать источники данных */
    QStringList choosen_data; // В переменной будет храниться столбцы, выбранные пользователем */
    TableColumnChooser chooser;
    chooser.set_headers(headers);
    chooser.set_input(_input);
    if (chooser.exec() == QDialog::Accepted) {
        choosen_data = chooser.get_headers();   // Если пользователь нажал ОК, то получаем выбранные столбцы
    } else
        return;
    /*Ищем индексы выбранных данных в списке заголовков*/
    for (int i = 0; i < choosen_data.size(); i++)
        _choosen_column.push_front(headers.indexOf(choosen_data.at(i)));

    /* По строке считываем данные из файла выборки. Они разделены табуляцией.
     *  Имя класса содержится в первом поле, значение x и y - в ячейках _index_x, _index_y соответственно */
    while(false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        QString class_name = row_list.at(0);
        QVector<double> data;
        for (int i = 0; i < _choosen_column.size(); i++)
            data.push_back(row_list.at(i).toDouble());
        /* Делаем соответствие между именем класса и его порядковым номером */
        if (false == _class_map.contains(class_name)) {
            if (true == _class_map.isEmpty())
                _class_map.insert(class_name, 1);
            else
                _class_map.insert(class_name, _class_map.size() + 1);
        }
        /* Создаем пример выборки и храним его в массиве примеров */
        NeuronExample example(data, _class_map.value(class_name));
        _teach_sample.push_back(example);
    }
    file.close();
    /* Создаём объект персептрона: количество нейронов - количество классов, 2 - число входов (x,y) */
//    _perceptron = Perceptron(_class_map.size(), 2);
//    _perceptron.InitWeights(1);
}


/**
 * Хаотично перемешивает примеры в выборке
 * @brief Classificator::ShakeExamples
 */
void MainWindow::ShakeExamples() {
    for (int i = 0; i < _teach_sample.size(); i++) {
        NeuronExample temp = _teach_sample[i];
        _teach_sample[i] = _teach_sample[qrand() % _teach_sample.size()];
        _teach_sample[qrand() % _teach_sample.size()] = temp;
    }
}


/**
 * Функция возвращает слой узлов (нейронов), используется при построении связей между нейронами
 * @brief MainWindow::GetLayout
 * @param index - номер слоя
 * @return
 */
QVector<QGVNode*> MainWindow::GetLayout(int index) const {
    QVector<QGVNode*> result;
    for (int i = 0; i < _neurons_in_layout; i++)
        result.push_back(_nodes[index][i]);
    return result;
}


/**
 * Функция строит рёбра между переданным и нейронами в слое
 * @brief MainWindow::AddEdges
 * @param node - нейрон
 * @param layout - слой
 */
void MainWindow::AddEdges(QGVNode *node, int layout) {
    QVector<QGVNode*> next_layout = GetLayout(layout + 1);
    for (int i = 0; i < next_layout.size(); i++)
        _scene -> addEdge(node, next_layout[i]);
}


/**
 * Создаёт на сцене визуальное представление входного вектора по количеству входов
 * @brief MainWindow::CreateInputNode
 */
void MainWindow::CreateInputNode() {
    QString input_label;
    for (int i = 0; i < _input; i++)
        input_label += "x" + QString::number(i + 1) + "\n";
    input_label.chop(1);
    QGVNode *input = _scene -> addNode(input_label);
    input -> setAttribute("shape", "box");
    AddEdges(input, -1);
}


/**
 * Создаёт на сцене визуальное представление выходного вектора по количеству выходов
 * @brief MainWindow::CreateOutputNode
 */
void MainWindow::CreateOutputNode() {
    QString output_label;
    for (int i = 0; i < _output; i++)
        output_label += "y" + QString::number(i + 1) + "\n";
    output_label.chop(1);
    QGVNode *output = _scene -> addNode(output_label);
    output -> setAttribute("shape", "box");
    QVector<QGVNode*> last_layer = GetLayout(_layout_count - 1);
    for (int i = 0; i < last_layer.size(); i++)
        _scene -> addEdge(last_layer[i], output);
}


/**
 * Слот, отвечающий за отрисовку сети
 * @brief MainWindow::SlotDrawGraph
 */
void MainWindow::SlotDrawGraph() {
    _scene -> clear();
    _nodes.clear();

    /* Установка основных параметров всей сети */
    _scene -> setGraphAttribute("splines", "spline");
    _scene -> setGraphAttribute("rankdir", "LR");
    _scene -> setGraphAttribute("nodesep", "1.0");
    /* Установка основных параметров узла */
    _scene -> setNodeAttribute("shape", "circle");
    _scene -> setNodeAttribute("style", "filled");
    _scene -> setNodeAttribute("fillcolor", "white");
    _scene -> setNodeAttribute("height", "1.2");

    /* Создание и добавление нейронов на сцену */
    int number = 1;
    for (int i = 0; i < _layout_count; i++) {
        QVector<QGVNode *> layer;
        for (int j = 0; j < _neurons_in_layout; j++) {
            QGVNode *node = _scene -> addNode(QString::number(number));
            layer.push_back(node);
            number++;
        }
        _nodes.push_back(layer);
    }
    /* Создаётся узел входного вектора */
    CreateInputNode();
    /* Создаются рёбра между элементами сети */
    for (int i = 0; i < _layout_count; i++)
        for (int j = 0; j < _neurons_in_layout; j++) {
        QGVNode *node = _nodes[i][j];
        if (i + 1 != _layout_count)
            AddEdges(node, i);
    }
    /* Создаётся узел выходного вектора */
    CreateOutputNode();
    _scene -> applyLayout();
    _ui -> _view -> fitInView(_scene -> sceneRect(), Qt::KeepAspectRatio);
}


/**
 * Слот, обрабатывающий нажатие кнопки 'Открыть файл с выборкой'
 * @brief MainWindow::on__action_open_triggered
 */
void MainWindow::on__action_open_sample_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с обучающей выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    if (true == file_name.isEmpty())
        return;

    CreateTeachSample(file_name);
    _ui -> _action_teach -> setEnabled(true);
}


/**
 * Слот, обрабатывающий нажатие кнопки 'Обучить сеть'
 * @brief MainWindow::on__action_teach_triggered
 */
void MainWindow::on__action_teach_triggered() {

}


/**
 * Слот, обрабатывающий нажатие кнопки 'Классифицировать данные'
 * @brief MainWindow::on__action_classificate_triggered
 */
void MainWindow::on__action_classificate_triggered() {

}


/**
 * Слот, обрабатывающий нажатие кнопки 'Конфигурация сети'
 * @brief MainWindow::on__action_network_settings_triggered
 */
void MainWindow::on__action_network_settings_triggered() {
    NeuronNetworkSettingsDialog dialog;
    dialog.set_input(_input);
    dialog.set_output(_output);
    dialog.set_layout_count(_layout_count);
    dialog.set_neurons_in_layout(_neurons_in_layout);
    if (dialog.exec() == QDialog::Accepted) {
        _input = dialog.get_input();
        _output = dialog.get_output();
        _layout_count = dialog.get_layout_count();
        _neurons_in_layout = dialog.get_neurons_in_layout();
        emit SignalNetworkSettingsChanged();
        _ui -> _action_open_sample -> setEnabled(true);
    }
}

