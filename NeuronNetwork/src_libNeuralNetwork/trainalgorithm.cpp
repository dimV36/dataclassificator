#include "trainalgorithm.h"

TrainAlgorithm::~TrainAlgorithm() {

}


Hebb::Hebb(NeuralNetwork *neural_network) {
    _neural_network = neural_network;
}


Hebb::~Hebb() {

}


void Hebb::WeightsInitialization() {

}


Backpropagation::Backpropagation(NeuralNetwork *neural_network) {
    _neural_network = neural_network;
}


Backpropagation::~Backpropagation() {

}


double Hebb::Train(const QVector<double> &data, const QVector<int> &target) {
    if (data.size() != _neural_network -> get_inputs() || target.size() != _neural_network -> get_outputs()) {
        qCritical() << "Входные данные не соответствуют входу сети";
        return false;
    } else {
        for (int index = 0; index < _neural_network -> get_inputs(); index++) {
            _neural_network -> GetInputLayer().at(index) -> Input(data[index]);
		}

        for (int layers = 0; layers < _neural_network -> size() - 1; layers++) {
            _neural_network -> GetBiasLayer().at(layers) -> Input(1.0);

            for (int index = 0; index < _neural_network -> GetLayer(layers).size(); index++) {
                _neural_network -> GetLayer(layers).at(index) -> Fire();
			}
            _neural_network -> GetBiasLayer().at(layers)->Fire();
		}

        QVector<int> response;
        for (int output = 0; output < _neural_network -> get_outputs(); output++) {
            double result = _neural_network -> GetOutputLayer().at(output) -> Fire();
            if (result > 0.0) {
                response.push_back(1);
            } else
                if (result == 0.0 ) {
                    response.push_back(0);
                } else {
                response.push_back(-1);
			}
		}

        for (int output = 0; output < _neural_network -> get_outputs(); output++) {
            if (response[output] != target[output]) {
                for (int layer = 0; layer < _neural_network -> _layers.size() - 1; layer++) {
                    for(int neuron = 0; neuron < _neural_network -> get_layers().at(layer).size(); neuron++) {
                        Neuron *current_input_neuron = (_neural_network -> get_layers().at(layer))[neuron];
                        for (int weight = 0; weight < current_input_neuron -> get_number_of_links(); weight++) {
                            current_input_neuron -> at(weight) -> set_weight(current_input_neuron -> at(weight) -> get_weight() + target[weight] * data[neuron]);
						}

					}
                    for (int weight = 0; weight < _neural_network -> GetBiasLayer().at(layer) -> get_number_of_links(); weight++) {
                        _neural_network -> GetBiasLayer().at(layer) -> at(weight) -> set_weight(_neural_network -> GetBiasLayer().at(layer) -> at(weight) -> get_weight() + target[weight] * 1);
					}

				}
                _neural_network -> ResetCharges();
				return false;
			}
		}
        _neural_network -> ResetCharges();
		return true;
	}

}



void Backpropagation::NguyenWidrowWeightsInitialization() {
    qsrand((int)QTime().secsTo(QTime::currentTime()));

    double inputs = _neural_network -> _inputs;
    double hidden = _neural_network -> _hidden;
    double degree = 1.0 / inputs ;
    double scale_factor = 0.7 * (qPow(hidden , degree));

    for (int layer = 0; layer < _neural_network -> size(); layer++) {
        for (int neuron = 0; neuron < _neural_network -> GetLayer(layer).size(); neuron++) {
            Neuron *current_neuron = _neural_network -> GetLayer(layer).at(neuron);
            for (int link = 0; link < current_neuron -> get_number_of_links(); link++) {
                NeuralLink *current_neural_link = current_neuron -> at(link);
                float pseudo_rand_weight = -0.5 + (float) qrand() / ((float)RAND_MAX/(0.5 + 0.5));
                current_neural_link -> set_weight(pseudo_rand_weight);
			}
		}
	}

    for (int neuron_hidden = 0; neuron_hidden < _neural_network -> GetLayer(1).size(); neuron_hidden++) {
        double squared_norm = 0;

        for (int neuron_input = 0; neuron_input < _neural_network -> GetLayer(0).size(); neuron_input++) {
            Neuron *current_input_neuron = _neural_network -> GetLayer(0).at(neuron_input);
            NeuralLink *current_neural_link = current_input_neuron -> at(neuron_hidden);
            squared_norm += qPow(current_neural_link -> get_weight(), 2.0);
		}

        double norm = qSqrt(squared_norm);

        for (int neuron_input = 0; neuron_input < _neural_network -> GetLayer(0).size(); neuron_input++) {
            Neuron *current_input_neuron = _neural_network -> GetLayer(0).at(neuron_input);
            NeuralLink *current_neural_link = current_input_neuron -> at(neuron_hidden);

            double new_weight = (scale_factor * (current_neural_link -> get_weight())) / norm;
            current_neural_link -> set_weight(new_weight);
		}

	}

    for (int layer = 0; layer < _neural_network->size() - 1; layer++) {
        Neuron *bias = _neural_network -> GetBiasLayer().at(layer);
        for (int link = 0; link < bias -> get_number_of_links(); link++) {
            NeuralLink *current_neural_link = bias -> at(link);
            float pseudo_rand_weight = -scale_factor + (float) qrand() / ((float)RAND_MAX / (scale_factor + scale_factor));
            current_neural_link -> set_weight(pseudo_rand_weight);
		}
	}
}


void Backpropagation::CommonInitialization() {

    qsrand((int)QTime().secsTo(QTime::currentTime()));

    for (int layer = 0; layer < _neural_network -> size(); layer++) {
        for (int neuron = 0; neuron < _neural_network -> GetLayer(layer).size(); neuron++) {
            Neuron *current_neuron = _neural_network -> GetLayer(layer).at(neuron);
            for (int link = 0; link < current_neuron -> get_number_of_links(); link++) {
                NeuralLink *current_neural_link = current_neuron -> at(link);
                float pseudo_rand_weight = -0.5 + (float) qrand() / ((float) RAND_MAX / (0.5 + 0.5));
                current_neural_link -> set_weight(pseudo_rand_weight);
			}
		}
	}

    for (int layer = 0; layer < _neural_network -> size() - 1; layer++) {
        Neuron *bias = _neural_network -> GetBiasLayer().at(layer);
        for (int link = 0; link < bias -> get_number_of_links(); link++) {
            NeuralLink *current_neural_link = bias -> at(link);
            float pseudo_rand_weight = -0.5 + (float) qrand() / ((float) RAND_MAX / (0.5 + 0.5));
            current_neural_link -> set_weight(pseudo_rand_weight);
		}
	}
}


void Backpropagation::WeightsInitialization() {
    NguyenWidrowWeightsInitialization();
}


double Backpropagation::Train(const QVector<double> &data, const QVector<int> &target) {

    double result = 0.0;
    if (data.size() != _neural_network -> _inputs || target.size() != _neural_network -> _outputs) {
        qCritical() << "Ошибка: количество выходов сети не соответствует входным данным сети \n";
		return -1;
    } else {

        for (int index = 0; index < _neural_network -> _inputs; index++)
            _neural_network -> GetInputLayer().at(index) -> Input(data[index]);


        for (int layer = 0; layer < _neural_network -> size() - 1; layer++) {
            _neural_network -> GetBiasLayer().at(layer) -> Input(1.0);
            for (int index = 0; index < _neural_network -> GetLayer(layer).size(); index++) {
                _neural_network -> GetLayer(layer).at(index) -> Fire();
			}
            _neural_network -> GetBiasLayer().at(layer) -> Fire();
            for (int i = 0; i < _neural_network -> GetBiasLayer().at(layer) -> get_number_of_links(); i++) {
                _neural_network -> GetBiasLayer().at(layer) -> get_links_to_neurons().at(i) -> set_last_translated_signal(1);
			}
		}

        QVector<double> response_y_k;
        for (int output = 0; output < _neural_network -> _outputs; output++) {
            double y_k = _neural_network -> GetOutputLayer().at(output) -> Fire();
            response_y_k.push_back(y_k);
		}

        for (int index = 0; index < _neural_network -> _outputs; index++) {
            result = _neural_network -> GetOutputLayer().at(index) -> PerformTrainingProcess(target[index]);
            _neural_network -> AddMSE(result);
		}

        for (int layer = _neural_network -> size() - 2; layer > 0 ; layer--) {
            for (int neuron = 0; neuron < _neural_network -> GetLayer(layer).size(); neuron++) {
                _neural_network -> GetLayer(layer).at(neuron) -> PerformTrainingProcess(0);
			}
		}
        _neural_network -> UpdateWeights();
        _neural_network -> ResetCharges();
		return result;
	}
}
