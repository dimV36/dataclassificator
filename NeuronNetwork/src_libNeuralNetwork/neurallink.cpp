#include "neurallink.h"


NeuralLink::NeuralLink() {
    _weight_to_neuron = 0.0;
    _neuron_linked_to = 0;
    _weight_correction_term = 0.0;
    _error_in_formation_term = 0.0;
    _last_translated_signal = 0.0;
}


NeuralLink::NeuralLink(Neuron *neuron_linked_to, double weight_to_neuron) {
    _weight_to_neuron = weight_to_neuron;
    _neuron_linked_to = neuron_linked_to;
    _weight_correction_term = 0.0;
    _error_in_formation_term = 0.0;
    _last_translated_signal = 0.0;
}


void NeuralLink::set_weight(double weight) {
    _weight_to_neuron = weight;
}


double NeuralLink::get_weight() const {
    return _weight_to_neuron;
}


void NeuralLink::set_neuron_linked_to(Neuron *neuron) {
    _neuron_linked_to = neuron;
}


Neuron *NeuralLink::get_neuron_linked_to() const {
    return _neuron_linked_to;
}


void NeuralLink::set_weight_correction_term(double weight_correction_term) {
    _weight_correction_term = weight_correction_term;
}


double NeuralLink::get_weight_correction_term() const {
    return _weight_correction_term;
}


void NeuralLink::set_error_in_formation_term(double term) {
    _error_in_formation_term = term;
}


double NeuralLink::get_error_in_formation_term() const {
    return _error_in_formation_term;
}


void NeuralLink::set_last_translated_signal(double signal) {
    _last_translated_signal = signal;
}


double NeuralLink::get_last_translated_signal() const {
    return _last_translated_signal;
}


void NeuralLink::UpdateWeight() {
    _weight_to_neuron = _weight_to_neuron + _weight_correction_term;
}

