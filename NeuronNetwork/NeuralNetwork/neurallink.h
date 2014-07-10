#ifndef NEURALLINK_H_
#define NEURALLINK_H_

class Neuron;

class NeuralLink {
protected:
    double _weight_to_neuron;
    Neuron *_neuron_linked_to;
    double _weight_correction_term;
    double _error_in_formation_term;
    double _last_translated_signal;

public:
    NeuralLink();
    NeuralLink(Neuron *neuron_linked_to, double weight_to_neuron = 0.0 );

    void set_weight(double weight);
    double get_weight() const;
  
    void set_neuron_linked_to(Neuron *neuron);
    Neuron *get_neuron_linked_to() const;
  
    void set_weight_correction_term(double weight_correction_term);
    double get_weight_correction_term() const;
  
    void set_error_in_formation_term(double term);
    double get_error_in_formation_term() const;

    void set_last_translated_signal(double signal);
    double get_last_translated_signal() const;

    void UpdateWeight();

};


#endif /* NEURALLINK_H_ */
