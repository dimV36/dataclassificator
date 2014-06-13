#include "classificator.h"
#include "ui_classificator.h"


/**
 * Конструктор класса Classificator
 * @brief Classificator::Classificator
 * @param parent
 */
Classificator::Classificator(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Classificator) {
    _ui -> setupUi(this);

    /* Отключаем кнопки обучения и классификации */
    _ui -> _action_teach -> setEnabled(false);
    _ui -> _action_classificate -> setEnabled(false);
    _ui -> _action_add_point -> setEnabled(false);
    _ui -> _action_color_settings -> setEnabled(false);
    /* Обновление цвета графика */
    connect(this, SIGNAL(SignalGraphColorWasChanged()), this, SLOT(SlotUpdateGraphColor()));
}

/**
 * Деструктор
 * @brief Classificator::~Classificator
 */
Classificator::~Classificator() {
    delete _ui;
}


/**
 * Создать тестовую выборку
 * @brief Classificator::CreateTeachSample
 * @param file_name
 */
void Classificator::CreateTeachSample(QString file_name) {
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
    if (chooser.exec() == QDialog::Accepted) {
        choosen_data = chooser.get_headers();   // Если пользователь нажал ОК, то получаем выбранные столбцы
    } else
        return;
    /*Ищем индексы выбранных данных в списке заголовков*/
    _index_x = headers.indexOf(choosen_data.at(0));
    _index_y = headers.indexOf(choosen_data.at(1));

    /* Устанавливаем значения осей графика */
    _ui -> _graph -> xAxis -> setLabel(choosen_data.at(0));
    _ui -> _graph -> yAxis -> setLabel(choosen_data.at(1));

    /* По строке считываем данные из файла выборки. Они разделены табуляцией.
     *  Имя класса содержится в первом поле, значение x и y - в ячейках _index_x, _index_y соответственно */
    while(false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        QString class_name = row_list.at(0);
        double x = row_list.at(_index_x).toDouble();
        double y = row_list.at(_index_y).toDouble();
        /* Делаем соответствие между именем класса и его порядковым номером */
        if (false == _class_map.contains(class_name)) {
            if (true == _class_map.isEmpty())
                _class_map.insert(class_name, 1);
            else
                _class_map.insert(class_name, _class_map.size() + 1);
            _color_map.insert(class_name, QColor().black());
        }
        /* Создаем пример выборки и храним его в массиве примеров */
        QVector<double> vector;
        vector.push_back(x);
        vector.push_back(y);
        NeuronExample example(vector, _class_map.value(class_name));
        _teach_sample.push_back(example);
    }
    file.close();
    /* Создаём объект персептрона: количество нейронов - количество классов, 2 - число входов (x,y) */
    _perceptron = Perceptron(_class_map.size(), 2);
    _perceptron.InitWeights(1);
}


/**
 * Вспомогательный метод, необходим для более чёткой установки min-max значений осей.
 * @brief Classificator::UpdateRange
 * @param range
 * @param value
 * @return
 */
QPair<int,int> Classificator::UpdateRange(QPair<int,int> range, double value) {
    if (floor(value) < range.first)
        range.first = floor(value);
    if (round(value) > range.second)
        range.second = round(value);
    return range;
}


/**
 * Хаотично перемешивает примеры в выборке
 * @brief Classificator::ShakeExamples
 */
void Classificator::ShakeExamples() {
    for (int i = 0; i < _teach_sample.size(); i++) {
        NeuronExample temp = _teach_sample[i];
        _teach_sample[i] = _teach_sample[qrand() % _teach_sample.size()];
        _teach_sample[qrand() % _teach_sample.size()] = temp;
    }
}


/**
 * Обработка нажатия кнопки 'Открыть файл с выборкой'
 * @brief Classificator::on__action_open_sample_triggered
 */
void Classificator::on__action_open_sample_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с обучающей выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    if (true == file_name.isEmpty())
        return;

    CreateTeachSample(file_name);
    _ui -> _action_teach -> setEnabled(true);
    _ui -> _action_color_settings -> setEnabled(true);
}


/**
 * Обработка нажатия кнопки 'Обучить'
 * @brief Classificator::on__action_teach_triggered
 */
void Classificator::on__action_teach_triggered() {
    int count = 0;   // Количество прогонов
    int speed = 0;   // Скорость обучения
    TeachProcess process;
    if (process.exec() == QDialog::Accepted) {
        count = process.get_count();
        speed = process.get_speed();
    } else
        return;
    _ui -> _status_bar -> showMessage(tr("Обучение начато"));
    while(count-- > 0) {
        for (int i = 0; i < _teach_sample.size(); i++) {
            ShakeExamples();
            QVector<double> example = _teach_sample[i].get_data(); // Получаем данные примера
            QVector<int> result = _perceptron.MakeOutputVector(_teach_sample[i]); // Создаём вектор, соответствующий классу
            _perceptron.Teach(example, result, speed); // Обучаем персептрон примеру
            _ui -> _status_bar -> showMessage(tr("Обучение примеру %1. Осталось %2 раз(а)").arg(i + 1).arg(count));
        }
    }
    _ui -> _status_bar -> showMessage(tr("Обучение завершено"));
    _ui -> _action_add_point -> setEnabled(true);
    _ui -> _action_classificate -> setEnabled(true);
}


/**
 * Обработка нажатия кнопки 'Классифицировать данные'
 * @brief Classificator::on__action_classificate_triggered
 */
void Classificator::on__action_classificate_triggered() {
    _ui -> _status_bar -> clearMessage();
    _ui -> _graph -> clearGraphs();                     // Очищаются все графики
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Выбрать файл с тестовой выборкой"),
                                                     QDir::currentPath(),
                                                     tr("Файлы выборки (*txt)"));
    if (true == file_name.isEmpty())
        return;

    QFile file(file_name);
    if (false == file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Ошибка при открытии файла тестовой выборки"),
                              tr("Невозможно открыть файл %1").arg(file_name));
        return;
    }
    _ui -> _graph -> legend -> setVisible(true);              // Показываем легенду
    /* На координатной плоскости создаём объекты графиков для всех классов */
    for (int i = 0; i < _class_map.size(); i++) {
        QString class_name = _class_map.key(i + 1);
        _ui -> _graph -> addGraph();
        _ui -> _graph ->graph(i) -> setLineStyle(QCPGraph::lsNone);
        QColor graph_color = _color_map.value(class_name);
        _ui -> _graph -> graph(i) -> setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, graph_color, graph_color, 4));
        /* Устанавливаем имя графику согласно карте соответствия */
        _ui -> _graph -> graph(i) -> setName(class_name);
    }
    while(false == file.atEnd()) {
        QStringList row_list = QString(file.readLine()).split('\t');
        double x = row_list.at(_index_x).toDouble();
        double y = row_list.at(_index_y).toDouble();

        /* Обновляем данные о минимальном/максимальном значении осей */
        _xrange = UpdateRange(_xrange, x);
        _yrange = UpdateRange(_yrange, y);

        QVector<double> vector;
        vector.push_back(x);
        vector.push_back(y);
        /* Получаем реакцию на вектор - определяем класс принодлежности */
        int class_name = _perceptron.GetClass(vector);
        /* Добавляем данные согласно классу */
        _ui -> _graph -> graph(class_name) -> addData(x, y);

    }
    /* Обновляем значение осей и перестраиваем график */
    _ui -> _graph -> xAxis -> setRange(_xrange.first, _xrange.second + 1);
    _ui -> _graph -> yAxis -> setRange(_yrange.first, _yrange.second + 1);
    _ui -> _graph -> replot();
    file.close();
}


/**
 * Обработка добавления точки на график
 * @brief Classificator::on__action_add_point_triggered
 */
void Classificator::on__action_add_point_triggered() {
    AddPointDialog dialog;
    double x, y;
    QVector<double> vector;
    if (dialog.exec() == QDialog::Accepted) {
        x = dialog.get_x();
        y = dialog.get_y();
    } else
        return;
    vector.push_back(x);
    vector.push_back(y);
    int class_number = _perceptron.GetClass(vector);

    _xrange = UpdateRange(_xrange, x);
    _yrange = UpdateRange(_yrange, y);

    _ui -> _graph -> graph(class_number) -> addData(x, y);
    _ui -> _graph -> xAxis -> setRange(_xrange.first, _xrange.second + 1);
    _ui -> _graph -> yAxis -> setRange(_yrange.first, _yrange.second + 1);
    _ui -> _graph -> replot();
}


/**
 * Настройка цветов классов
 * @brief Classificator::on__action_settings_triggered
 */
void Classificator::on__action_color_settings_triggered() {
    ColorChooserDialog dialog;
    dialog.set_classmap(_color_map);
    if (dialog.exec() == QDialog::Accepted) {
        _color_map = dialog.get_classmap();
    }
    /* Высылаем сигнал обновления цветов, если количество графиков не равно 0 */
    if (false == (0 == _ui -> _graph -> graphCount()))
        emit SignalGraphColorWasChanged();
}


/**
 * Слот обновления цвета
 * @brief Classificator::SlotUpdateGraphColor
 */
void Classificator::SlotUpdateGraphColor() {
    for (int i = 0; i < _class_map.size(); i++) {
        QString class_name = _class_map.key(i + 1);
        QColor graph_color = _color_map.value(class_name);
        _ui -> _graph -> graph(i) -> setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, graph_color, graph_color, 4));
    }
    _ui -> _graph -> replot();
}
