#include "tablecolumnchooser.h"
#include "ui_tablecolumnchooser.h"


TableColumnChooser::TableColumnChooser(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::TableColumnChooser) {
    _ui -> setupUi(this);
    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));
    _ui -> _button_box -> button(_ui -> _button_box -> Ok) -> setEnabled(false);
    /* Подключение сигналов и обрабатывающих их слотов */
    connect(_ui -> _list_input_columns, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SlotAddItemToChoosenList(QListWidgetItem *)));
    connect(_ui -> _list_choosen_columns, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SlotRemoveItemFromChoosenList(QListWidgetItem*)));
    connect(this, SIGNAL(SignalItemCountInListChanged(int)), this, SLOT(SlotSetEnabledOkButton(int)));
}


TableColumnChooser::~TableColumnChooser() {
    delete _ui;
}


/**
 * Добавление заголовков в таблицу
 * @brief TableColumnChooser::set_headers
 * @param headers
 */
void TableColumnChooser::set_headers(QStringList headers) {
    _ui -> _list_input_columns -> addItems(headers);
}


/**
 * Установить количество входов
 * @brief TableColumnChooser::set_input
 * @param input
 */
void TableColumnChooser::set_input(const int input) {
    _input = input;
}


/**
 * Получение выбранных пользователем данных
 * @brief TableColumnChooser::get_headers
 * @return
 */
QStringList TableColumnChooser::get_headers() const {
    QStringList result;
    for (int i = 0; i < _ui -> _list_choosen_columns -> count(); i++)
        result.append(_ui -> _list_choosen_columns -> item(i) -> text());
    return result;
}


/**
 * Слот обработки добавления в список выбранных
 * @brief TableColumnChooser::SlotAddItemToChoosenList
 * @param item
 */
void TableColumnChooser::SlotAddItemToChoosenList(QListWidgetItem *item) {
    if ( _ui -> _list_choosen_columns -> count() < _input) {
        int index = _ui -> _list_input_columns -> row(item);
        _ui -> _list_input_columns -> takeItem(index);
        _ui -> _list_choosen_columns -> addItem(item);
        emit SignalItemCountInListChanged( _ui -> _list_choosen_columns -> count());
    }
}


/**
 * Слот обработки исключения из списка выбранных
 * @brief TableColumnChooser::SlotRemoveItemFromChoosenList
 * @param item
 */
void TableColumnChooser::SlotRemoveItemFromChoosenList(QListWidgetItem *item) {
    int index = _ui -> _list_choosen_columns -> row(item);
    _ui -> _list_choosen_columns -> takeItem(index);
    _ui -> _list_input_columns -> addItem(item);
    emit SignalItemCountInListChanged( _ui -> _list_choosen_columns -> count());
}


/**
 * Слот установки кнопки активной
 * @brief TableColumnChooser::SlotSetEnabledOkButton
 * @param count
 */
void TableColumnChooser::SlotSetEnabledOkButton(int count) {
    bool enabled = false;
    if (count == _input)
        enabled = true;
    _ui -> _button_box -> button(_ui -> _button_box -> Ok) -> setEnabled(enabled);
}
