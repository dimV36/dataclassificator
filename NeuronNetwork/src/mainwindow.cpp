#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    connect(this, SIGNAL(SignalWeightsWereChanged()), this, SLOT(SlotDrawGraph()));

    /* Создание сцены, на которой отрисовывается сеть */
    _scene = new QGVScene(QString());
    _ui -> _view -> setScene(_scene);

    _inputs = _outputs = _hidden_layer_size = _neurons_in_hidden_layer = 1;
    _function = LinearFunction;

    qsrand(QTime().secsTo(QTime().currentTime()));
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
    if (chooser.exec() == QDialog::Accepted)
        choosen_data = chooser.get_headers();   // Если пользователь нажал ОК, то получаем выбранные столбцы
    else
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
 * @brief MainWindow::GetNodeLayer
 * @param index - номер слоя
 * @return
 */
QVector<Node*> MainWindow::GetNodeLayer(int index) const {
    QVector<Node*> result;
    for (int i = 0; i < _neurons_in_hidden_layer; i++)
        result.push_back(_hidden_layer[index][i]);
    return result;
}


/**
 * Функция преобразовывает номер класса в идентичный в вектороной форме
 * @brief MainWindow::ConvertClassToVector
 * @param class_number - номер класса
 * @return преобразованный вектор
 */
QVector<int> MainWindow::ConvertClassToVector(int class_number) const {
    QVector<int> result = QVector<int>(_outputs);
    for (int i = 0; i < result.size(); i++) {
        if (i == class_number - 1)
            result[i] = 1;
    }
    return result;
}


/**
 * Функция преобразовывает вектор вывода сети в имя класса
 * @brief MainWindow::ConvertVectorToClass
 * @param output
 * @return
 */
QString MainWindow::ConvertVectorToClass(QVector<int> output)  {
    int coordinate = qrand() % output.size();
    output[coordinate] = 1;
    for (int i = 0; i < output.size(); i++) {
        if (output[i] == 1)
            return _class_map.key(i + 1);
    }
    return tr("Класс не определён сетью");
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
    _scene -> setGraphAttribute("nodesep", "2.0");
    _scene -> setGraphAttribute("ranksep", "3");

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
        QVector<Node *> hidden_layer = GetNodeLayer(0);
        Node *input = _input_layer[i];
        for (int j = 0; j < hidden_layer.size(); j++) {
            QString weight = QString::number(_network -> GetInputLayer()[i] -> get_links_to_neurons()[j] -> get_weight());
            while (weight.size() > 7)
                weight.chop(1);
            input -> AddEdge(hidden_layer[j], weight);
        }
    }

    /* Создаются связи между элементами скрытого слоя */
    for (int i = 0; i < _hidden_layer_size; i++)
        for (int j = 0; j < _neurons_in_hidden_layer; j++) {
        Node *node = _hidden_layer[i][j];
        if (i + 1 != _hidden_layer_size) {
            QVector<Node*> next_layout = GetNodeLayer(i + 1);
            for (int j = 0; j < next_layout.size(); j++) {
                QString weight = QString::number(_network -> GetLayer(i)[i] -> get_links_to_neurons()[j] -> get_weight());
                while (weight.size() > 7)
                    weight.chop(1);
                node -> AddEdge(next_layout[j], weight);
            }
        }
    }

    /* Создаются связи между скрытым слоем и выходящим */
    for (int i = 0; i < _neurons_in_hidden_layer; i++) {
        QVector<Node*> hidden_layer = GetNodeLayer(_hidden_layer_size - 1);
        QVector<Neuron*> hidden = _network -> GetLayer(_hidden_layer_size);
        for (int j = 0; j < _outputs; j++) {
            QString weigth = QString::number(hidden[i] -> get_links_to_neurons()[j] -> get_weight());
            while (weigth.size() > 7)
                weigth.chop(1);
            hidden_layer[i] -> AddEdge(_output_layer[j], weigth);
        }
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
    int index = 0;
    while (index < _teach_sample.GetSampleSize()) {
        NeuralNetworkExample example = _teach_sample[index];
        _network -> Train(example.first, example.second);
        _ui -> _status_bar -> showMessage(tr("Обучение примеру %1 из %2").arg(index + 1).arg(_teach_sample.GetSampleSize()));
        if ((index % 10 == 0) || (index == _teach_sample.GetSampleSize()))
            emit SignalWeightsWereChanged();
        index++;
    }
    _ui -> _status_bar -> showMessage(tr("Обучение завершено"), 10000);
    _ui -> _action_classificate -> setEnabled(true);
}



/**
 * Слот, обрабатывающий нажатие кнопки 'Классифицировать данные'
 * @brief MainWindow::on__action_classificate_triggered
 */
void MainWindow::on__action_classificate_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с тестовой выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    if (true == file_name.isEmpty())
        return;

    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    QList<QPair<QString, QString> > results;
    file.readLine();
    while (false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        QString class_name = row_list.at(0);
        QVector<double> data;
        for (int i = 0; i < _choosen_column.size(); i++)
            data.push_back(row_list.at(i).toDouble());
        QString class_of_example = ConvertVectorToClass(_network -> NetResponse(data));
        results.push_back(QPair<QString, QString>(class_name, class_of_example));
    }
    file.close();
    ClassificatorDialog dialog;
    dialog.set_data(results);
    if (dialog.exec() == QDialog::Accepted) {
        QStringList results = dialog.get_statistic();
        QString file_name = dialog.get_file_name();

        QFile file(file_name);
        if (false == file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this,
                                  tr("Ошибка при открытии файла"),
                                  tr("Невозможно открыть файл %1 для записи.").arg(file_name));
            return;
        }
        QTextStream out(&file);
        out << _network -> GetInformationAboutNetwork();
        for (int i = 0; i < results.size(); i++)
            out << results[i];
        file.close();
    }
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
        CreateNetwork();
        emit SignalWeightsWereChanged();
        _ui -> _action_open_sample -> setEnabled(true);
        _ui -> _action_teach -> setEnabled(false);
        _ui -> _action_classificate -> setEnabled(false);
    }
}
