#include "tablecolumnchooser.h"
#include "ui_tablecolumnchooser.h"


TableColumnChooser::TableColumnChooser(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::TableColumnChooser) {
    _ui -> setupUi(this);
    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));
    _ui -> _button_box -> button(_ui -> _button_box -> Ok) -> setEnabled(false);

    connect(_ui -> _list_input_columns, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SlotAddItemToChoosenList(QListWidgetItem *)));
    connect(_ui -> _list_choosen_columns, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SlotRemoveItemFromChoosenList(QListWidgetItem*)));
    connect(this, SIGNAL(SignalItemCountInListChanged(int)), this, SLOT(SlotSetEnabledOkButton(int)));
}


TableColumnChooser::~TableColumnChooser() {
    delete _ui;
}


void TableColumnChooser::set_headers(QStringList headers) {
    _ui -> _list_input_columns -> addItems(headers);
}


QStringList TableColumnChooser::get_headers() const {
    QStringList result;
    for (int i = 0; i < _ui -> _list_choosen_columns -> count(); i++)
        result.append(_ui -> _list_choosen_columns -> item(i) -> text());
    return result;
}


void TableColumnChooser::SlotAddItemToChoosenList(QListWidgetItem *item) {
    if ( _ui -> _list_choosen_columns -> count() < 2) {
        int index = _ui -> _list_input_columns -> row(item);
        _ui -> _list_input_columns -> takeItem(index);
        _ui -> _list_choosen_columns -> addItem(item);
        emit SignalItemCountInListChanged( _ui -> _list_choosen_columns -> count());
    }
}


void TableColumnChooser::SlotRemoveItemFromChoosenList(QListWidgetItem *item) {
    int index = _ui -> _list_choosen_columns -> row(item);
    _ui -> _list_choosen_columns -> takeItem(index);
    _ui -> _list_input_columns -> addItem(item);
    emit SignalItemCountInListChanged( _ui -> _list_choosen_columns -> count());
}


void TableColumnChooser::SlotSetEnabledOkButton(int count) {
    bool enabled = false;
    if (count == 2)
        enabled = true;
    _ui -> _button_box -> button(_ui -> _button_box -> Ok) -> setEnabled(enabled);
}
