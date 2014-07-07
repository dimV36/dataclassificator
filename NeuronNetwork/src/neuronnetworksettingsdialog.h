#ifndef NEURONNETWORKSETTINGSDIALOG_H
#define NEURONNETWORKSETTINGSDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "neuralnetwork.h"

namespace Ui {
class NeuronNetworkSettingsDialog;
}

class NeuronNetworkSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeuronNetworkSettingsDialog(QWidget *parent = 0);
    ~NeuronNetworkSettingsDialog();

    int get_inputs() const;
    int get_outputs() const;
    int get_hidden_layer_size() const;
    int get_neurons_in_hidden_layer() const;
    ActivationFunction get_activation_function() const;

    void set_inputs(const int value);
    void set_outputs(const int value);
    void set_hidden_layer_size(const int value);
    void set_neurons_in_hidden_layer(const int value);
    void set_activation_function(ActivationFunction code);
private:
    Ui::NeuronNetworkSettingsDialog *_ui;
};

#endif // NEURONNETWORKSETTINGSDIALOG_H
