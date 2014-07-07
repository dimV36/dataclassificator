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

    _inputs = _outputs = _hidden_layer_size = _neurons_in_hidden_layer = 1;
    _function = LinearFunction;
}

/**
 * Деструктор класса
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete _ui;
}


/**
 * Создание многослойной нейронной сети
 * @brief MainWindow::CreateNetwork
 */
void MainWindow::CreateNetwork() {
    _network = new NeuralNetwork(_inputs, _outputs, _hidden_layer_size, _neurons_in_hidden_layer);
}


/**
 * Создать тестовую выборку
 * @brief Classificator::CreateTeachSample
 * @param file_name
 */
void MainWindow::CreateTeachSample(QString file_name) {
    _teach_sample.Clear();
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
    chooser.set_input(_inputs);
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
        _teach_sample.Push(data, ConvertClassToVector(_class_map.value(class_name)));
    }
    file.close();
}


/**
 * Хаотично перемешивает примеры в выборке
 * @brief Classificator::ShakeExamples
 */
void MainWindow::ShakeExamples() {
    for (int i = 0; i < _teach_sample.GetSampleSize(); i++) {
        NeuralNetworkExample temp = _teach_sample.GetExample(i);
        _teach_sample[i] = _teach_sample[qrand() % _teach_sample.GetSampleSize()];
        _teach_sample[qrand() % _teach_sample.GetSampleSize()] = temp;
    }
}


/**
 * Функция возвращает слой узлов (нейронов), используется при построении связей между нейронами
 * @brief MainWindow::GetLayout
 * @param index - номер слоя
 * @return
 */
QVector<Node*> MainWindow::GetLayout(int index) const {
    QVector<Node*> result;
    for (int i = 0; i < _neurons_in_hidden_layer; i++)
        result.push_back(_hidden_layer[index][i]);
    return result;
}


/**
 * Функция строит рёбра между переданным и скрытыми нейронами
 * @brief MainWindow::AddEdges
 * @param node - нейрон
 * @param layout - слой
 */
void MainWindow::AddEdges(Node *node, int layout) {
    QVector<Node*> next_layout = GetLayout(layout + 1);
    for (int i = 0; i < next_layout.size(); i++)
        node -> AddEdge(next_layout[i], "0");
}


/**
 * Функция преобразовывает номер класса в идентичный в вектороной форме
 * @brief MainWindow::ConvertClassToVector
 * @param class_number - номер класса
 * @return преобразованный вектор
 */
QVector<int> MainWindow::ConvertClassToVector(int class_number) {
    QVector<int> result = QVector<int>(_outputs);
    for (int i = 0; i < result.size(); i++) {
        if (i == class_number - 1)
            result[i] = 1;
    }
    return result;
}


/**
 * Метод обновляет связи между нейронами на графике
 * @brief MainWindow::UpdateLinksOnGraph
 */
void MainWindow::UpdateLinksOnGraph() {
    QVector<Neuron*> input_layer = _network -> GetInputLayer();
    for (int i = 0; i < input_layer.size(); i++) {
        Neuron *neuron = input_layer[i];
        Node *node = _input_layer[i];
        QVector<Node*> hidden = GetLayout(0);
        QVector<NeuralLink*> links = neuron -> get_links_to_neurons();
        for (int j = 0; j < links.size(); j++) {
            QString weight = QString::number(links[j] -> get_weight());
            node -> get_edges()[j] -> setLabel(weight);
            _scene -> applyLayout();
            _ui -> _view -> fitInView(_scene -> sceneRect(), Qt::KeepAspectRatio);
        }
    }
}


/**
 * Слот, отвечающий за отрисовку сети
 * @brief MainWindow::SlotDrawGraph
 */
void MainWindow::SlotDrawGraph() {
    _scene -> clear();
    _input_layer.clear();
    _hidden_layer.clear();
    _output_layer.clear();

    /* Установка основных параметров всей сети */
    _scene -> setGraphAttribute("splines", "spline");
    _scene -> setGraphAttribute("rankdir", "LR");
    _scene -> setGraphAttribute("nodesep", "1.0");
    /* Установка основных параметров узла */
    _scene -> setNodeAttribute("shape", "circle");
    _scene -> setNodeAttribute("style", "filled");
    _scene -> setNodeAttribute("fillcolor", "white");
    _scene -> setNodeAttribute("height", "1.2");

    /* Создание и добавление на сцену нейронов входного слоя */
    int number = 1;
    for (int i = 0; i < _inputs; i++) {
        Node *input_node = new Node(_scene, QString::number(number));
        _input_layer.push_back(input_node);
        number++;
        input_node -> get_node() -> setAttribute("fillcolor", "red");
    }

    /* Создание и добавление нейронов скрытого слоя на сцену */
    number = 1;
    for (int i = 0; i < _hidden_layer_size; i++) {
        QVector<Node *> layer;
        for (int j = 0; j < _neurons_in_hidden_layer; j++) {
            Node *node = new Node(_scene, QString::number(number));
            layer.push_back(node);
            number++;
        }
        _hidden_layer.push_back(layer);
    }

    /* Создание и добавление на сцену нейронов выходного слоя */
    number = 1;
    for (int i = 0; i < _outputs; i++) {
        Node *input_node = new Node(_scene ,QString::number(number));
        _output_layer.push_back(input_node);
        number++;
        input_node -> get_node() -> setAttribute("fillcolor", "blue");
    }

    /* Создаются связи между входным слоем и скрытым */
    for (int i = 0; i < _inputs; i++) {
        QVector<Node *> hidden_layer = GetLayout(0);
        Node *input = _input_layer[i];
        for (int j = 0; j < hidden_layer.size(); j++) {
            input -> AddEdge(hidden_layer[j], "0");
        }
    }

    /* Создаются связи между элементами скрытого слоя */
    for (int i = 0; i < _hidden_layer_size; i++)
        for (int j = 0; j < _neurons_in_hidden_layer; j++) {
        Node *node = _hidden_layer[i][j];
        if (i + 1 != _hidden_layer_size)
            AddEdges(node, i);
    }

    /* Создаются связи между скрытым слоем и выходящим */
    for (int i = 0; i < _outputs; i++) {
        QVector<Node*> hidden_layer = GetLayout(_hidden_layer_size - 1);
        Node *output = _output_layer[i];
        for (int j = 0; j < hidden_layer.size(); j++)
            hidden_layer[j] -> AddEdge(output, "0");
    }

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
    for (int i = 0; i < _teach_sample.GetSampleSize(); i++) {
        NeuralNetworkExample example = _teach_sample[i];
        _network -> Train(example.first, example.second);
        _ui -> _status_bar -> showMessage(tr("Обучение примеру %1").arg(i + 1), 100);
        UpdateLinksOnGraph();
    }
}


/**
 * Слот, обрабатывающий нажатие кнопки 'Классифицировать данные'
 * @brief MainWindow::on__action_classificate_triggered
 */
void MainWindow::on__action_classificate_triggered() {
    _input_layer[0] -> get_node() -> setLabel("2");
}


/**
 * Слот, обрабатывающий нажатие кнопки 'Конфигурация сети'
 * @brief MainWindow::on__action_network_settings_triggered
 */
void MainWindow::on__action_network_settings_triggered() {
    NeuronNetworkSettingsDialog dialog;
    dialog.set_inputs(_inputs);
    dialog.set_outputs(_outputs);
    dialog.set_hidden_layer_size(_hidden_layer_size);
    dialog.set_neurons_in_hidden_layer(_neurons_in_hidden_layer);
    dialog.set_activation_function(_function);
    if (dialog.exec() == QDialog::Accepted) {
        _inputs = dialog.get_inputs();
        _outputs = dialog.get_outputs();
        _hidden_layer_size = dialog.get_hidden_layer_size();
        _neurons_in_hidden_layer = dialog.get_neurons_in_hidden_layer();
        _function = dialog.get_activation_function();
        emit SignalNetworkSettingsChanged();
        _ui -> _action_open_sample -> setEnabled(true);
    }
    CreateNetwork();
}

