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

    int get_input() const;
    int get_output() const;
    int get_layout_count() const;
    int get_neurons_in_layout() const;
    ActivationFunction get_activation_function() const;

    void set_input(const int value);
    void set_output(const int value);
    void set_layout_count(const int value);
    void set_neurons_in_layout(const int value);
    void set_activation_function(ActivationFunction code);
private:
    Ui::NeuronNetworkSettingsDialog *_ui;
};

#endif // NEURONNETWORKSETTINGSDIALOG_H
