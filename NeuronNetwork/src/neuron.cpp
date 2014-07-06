#include "neuron.h"


Neuron::Neuron() {
    _network_function = new Linear();
    _sum_of_charges = 0.0;
}


Neuron::Neuron(NetworkFunction *function) {
    _network_function = function;
    _sum_of_charges = 0.0;
}


Neuron::Neuron(QVector<NeuralLink *> links_to_neurons, NetworkFunction *function) {
    _network_function = function;
    _links_to_neurons = links_to_neurons;
    _sum_of_charges = 0.0;
}


Neuron::Neuron(QVector<Neuron*> &neurons_link_to, NetworkFunction *function) {

    _network_function = function;
    _sum_of_charges = 0.0;
    for (int i = 0; i < neurons_link_to.size(); i++) {
        NeuralLink *link = new NeuralLink (neurons_link_to[i], 0.0 );
        _links_to_neurons.push_back(link);
        neurons_link_to[i] -> set_input_link(link);
	}

}


Neuron::~Neuron() {

}


QVector<NeuralLink*> Neuron::get_links_to_neurons() const {
    return _links_to_neurons;
}


NeuralLink* Neuron::at(const int index_of_neural_link) {
    return _links_to_neurons.at(index_of_neural_link);
}


void Neuron::set_link_to_neuron(NeuralLink *link) {
    _links_to_neurons.push_back(link);
}


void Neuron::Input(double input_data) {
    _sum_of_charges += input_data;
}


double Neuron::Fire() {
    for(int link = 0; link < this -> get_number_of_links(); link++){
        NeuralLink* current_link = _links_to_neurons[link];
        Neuron* current_neuron_linked_to = current_link -> get_neuron_linked_to();

        double weight = current_link -> get_weight();
        double charge = _sum_of_charges;
        double x_i = (_network_function -> Process(charge));
        double output = x_i * weight;

        current_link -> set_last_translated_signal(x_i);
        current_neuron_linked_to -> Input(output);
    }
    return _sum_of_charges;
}


int Neuron::get_number_of_links() const {
    return _links_to_neurons.size();
}


double Neuron::get_sum_of_charges() const {
    return _sum_of_charges;
}


void Neuron::ResetSumOfCharges() {
    _sum_of_charges = 0.0;
}


double Neuron::Process() {
    return _network_function -> Process(_sum_of_charges);
}


double Neuron::Process(double value) {
    return _network_function -> Process(value);
}


double Neuron::Derivative() {
    return _network_function -> Derivative(_sum_of_charges);
}


void Neuron::set_input_link(NeuralLink *link) {
    _input_links.push_back(link);
}


QVector<NeuralLink*> Neuron::get_input_links() const {
    return _input_links;
}


double Neuron::PerformTrainingProcess(double) {
    return 0.0;
}


void Neuron::PerformWeightsUpdating() {

}


void Neuron::ShowNeuronState() {
    for (int i = 0; i < _links_to_neurons.size(); i++) {
        NeuralLink *link = _links_to_neurons.at(i);
        qDebug() << "    Link index: " << i;
        qDebug() << "      Weight: " << link -> get_weight() << "; Weight correction term: " << link -> get_weight_correction_term();
    }
}



/**************************** Реализация методов класса OutputLayerNeuron ****************************/
OutputLayerNeuron::OutputLayerNeuron(Neuron *neuron) {
    _output_charge = 0.0;
    _neuron = neuron;
}


OutputLayerNeuron::~OutputLayerNeuron() {
    delete _neuron;
}


QVector<NeuralLink*> OutputLayerNeuron::get_input_links() const {
    return _neuron -> get_input_links();
}


NeuralLink* OutputLayerNeuron::at(int index) {
    return _neuron -> at(index);
}


void OutputLayerNeuron::set_link_to_neuron(NeuralLink *link) {
    _neuron -> set_link_to_neuron(link);
}


double OutputLayerNeuron::get_sum_of_charges() const {
    return _neuron -> get_sum_of_charges();
}


QVector<NeuralLink*> OutputLayerNeuron::get_links_to_neurons() const {
    return _neuron -> get_links_to_neurons();
}



void OutputLayerNeuron::ResetSumOfCharges() {
    _neuron -> ResetSumOfCharges();
}


void OutputLayerNeuron::Input(double input_data) {
    _neuron -> Input(input_data);
}


double OutputLayerNeuron::Fire() {
    double output = this -> Process();
    _output_charge = output;
    return output;
}


int OutputLayerNeuron::get_number_of_links() const {
    return _neuron -> get_number_of_links();
}


double OutputLayerNeuron::Process() {
    return _neuron -> Process();
}


double OutputLayerNeuron::Process(double value) {
    return _neuron -> Process(value);
}


double OutputLayerNeuron::Derivative() {
    return _neuron -> Derivative();
}


void OutputLayerNeuron::set_input_link(NeuralLink *link) {
    _neuron -> set_input_link(link);
}


double OutputLayerNeuron::PerformTrainingProcess(double target) {
    double result;
    double error_in_formation_term = (target - _output_charge) * _neuron -> Derivative();
    result = qPow(target - _output_charge, 2);
    for (int i = 0; i < (this -> get_input_links()).size(); i++) {
        NeuralLink *input_link = (this -> get_input_links()).at(i);
        double z_j = input_link -> get_last_translated_signal();
        double weight_correction_term = z_j * error_in_formation_term;
        input_link -> set_weight_correction_term(LEARNING_RATE * weight_correction_term);
        input_link -> set_error_in_formation_term(error_in_formation_term);
    }
    return result;
}


void OutputLayerNeuron::PerformWeightsUpdating() {
    for (int i = 0; i < (this -> get_input_links()).size(); i++) {
        NeuralLink *input_link = (this -> get_input_links()).at(i);
        input_link -> UpdateWeight();;
    }
}


void OutputLayerNeuron::ShowNeuronState() {
    _neuron -> ShowNeuronState();
}


/**************************** Реализация методов класса HiddenLayerNeuron ****************************/


HiddenLayerNeuron::HiddenLayerNeuron(Neuron *neuron) {
    _neuron = neuron;
}


HiddenLayerNeuron::~HiddenLayerNeuron() {
    delete _neuron;
}


QVector<NeuralLink*> HiddenLayerNeuron::get_input_links() const {
    return _neuron -> get_links_to_neurons();
}


NeuralLink* HiddenLayerNeuron::at(int index) {
    return _neuron -> at(index);
}


void HiddenLayerNeuron::set_link_to_neuron(NeuralLink *link) {
    _neuron -> set_link_to_neuron(link);
}


double HiddenLayerNeuron::get_sum_of_charges() const {
    return _neuron -> get_sum_of_charges();
}


QVector<NeuralLink*> HiddenLayerNeuron::get_links_to_neurons() const {
    return _neuron -> get_links_to_neurons();
}


void HiddenLayerNeuron::ResetSumOfCharges() {
    _neuron -> ResetSumOfCharges();
}


void HiddenLayerNeuron::Input(double input_data) {
    _neuron -> Input(input_data);
}


double HiddenLayerNeuron::Fire() {
    for (int i = 0; i < this -> get_number_of_links(); i++) {
        NeuralLink *current_link = _neuron -> at(i);
        Neuron *current_neuron_linked_to = current_link -> get_neuron_linked_to();

        const double weight = _neuron -> at(i) -> get_weight();
        double	charge = _neuron -> get_sum_of_charges();
        double	z_j = _neuron -> Process(charge);
        double 	output = z_j * weight;

        current_link -> set_last_translated_signal(z_j);
        current_neuron_linked_to -> Input(output);
    }
    return _neuron -> get_sum_of_charges();
}


int HiddenLayerNeuron::get_number_of_links() const {
    return _neuron -> get_number_of_links();
}


double HiddenLayerNeuron::Process() {
    return _neuron -> Process();
}


double HiddenLayerNeuron::Process(double value) {
    return _neuron -> Process(value);
}


double HiddenLayerNeuron::Derivative() {
    return _neuron -> Derivative();
}


void HiddenLayerNeuron::set_input_link(NeuralLink *link) {
    _neuron -> set_input_link(link);
}


double HiddenLayerNeuron::PerformTrainingProcess(double /*target*/) {
    double delta_inputs = 0.0;
    for (int i = 0; i < this -> get_number_of_links(); i++) {
        NeuralLink *output_link = this -> get_links_to_neurons().at(i);
        double error_in_formation_term = output_link -> get_error_in_formation_term();
        double weight = output_link -> get_weight();
        delta_inputs = delta_inputs + weight * error_in_formation_term;
    }
    double error_in_formation_term_j = delta_inputs * this -> Derivative();
    for (int i = 0; i < this -> get_input_links().size(); i++) {
        NeuralLink *input_link = this -> get_input_links().at(i);
        double x_i = input_link -> get_last_translated_signal();
        double weight_correction_term = x_i * error_in_formation_term_j;
        input_link -> set_weight_correction_term(LEARNING_RATE * weight_correction_term);
        input_link -> set_error_in_formation_term(error_in_formation_term_j);
    }
    return 0;
}


void HiddenLayerNeuron::PerformWeightsUpdating() {
    for (int i = 0; i < (this -> get_input_links()).size(); i++) {
        NeuralLink *input_link = (this -> get_input_links()).at(i);
        input_link -> UpdateWeight();
    }
}


void HiddenLayerNeuron::ShowNeuronState() {
    _neuron -> ShowNeuronState();
}
