#include "neuronnetworksettingsdialog.h"
#include "ui_neuronnetworksettingsdialog.h"

NeuronNetworkSettingsDialog::NeuronNetworkSettingsDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NeuronNetworkSettingsDialog) {
    _ui -> setupUi(this);

    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));
}


NeuronNetworkSettingsDialog::~NeuronNetworkSettingsDialog() {
    delete _ui;
}


int NeuronNetworkSettingsDialog::get_input() const {
    return _ui -> _box_input -> value();
}


int NeuronNetworkSettingsDialog::get_output() const {
    return _ui -> _box_output -> value();
}


int NeuronNetworkSettingsDialog::get_layout_count() const {
    return _ui -> _box_layout_count -> value();
}


int NeuronNetworkSettingsDialog::get_neurons_in_layout() const {
    return _ui -> _box_neutons_in_layout -> value();
}


ActivationFunction NeuronNetworkSettingsDialog::get_activation_function() const {
    int choosen_row = _ui -> _box_activation_function -> currentIndex();
    return ActivationFunction(choosen_row);
}


void NeuronNetworkSettingsDialog::set_input(const int value) {
    _ui -> _box_input -> setValue(value);
}


void NeuronNetworkSettingsDialog::set_output(const int value) {
    _ui -> _box_output -> setValue(value);
}


void NeuronNetworkSettingsDialog::set_layout_count(const int value) {
    _ui -> _box_layout_count -> setValue(value);
}


void NeuronNetworkSettingsDialog::set_neurons_in_layout(const int value) {
    _ui -> _box_neutons_in_layout -> setValue(value);
}


void NeuronNetworkSettingsDialog::set_activation_function(ActivationFunction code) {
    _ui -> _box_activation_function -> setCurrentIndex(code);
}
