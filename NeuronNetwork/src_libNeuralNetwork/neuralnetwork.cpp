#include "neuralnetwork.h"


NeuralNetwork::NeuralNetwork(int inputs, int outputs, int number_of_hidden_layers, int number_of_neurons_in_hidden_layers, ActivationFunction function) {
    if (inputs > 0 && outputs > 0) {
        _min_mean_squared_error = 0.01;
        _mean_squared_error = 0;
        _inputs = inputs;
        _outputs = outputs;
        _hidden = number_of_neurons_in_hidden_layers;

        NetworkFunction *input_neurons_function = new Linear();
        NetworkFunction *output_neurons_function = 0;

        switch(function) {
            case LinearFunction: {
                output_neurons_function = new Linear();
                break;
            }
            case SigmoidFunction: {
                output_neurons_function = new Sigmoid();
                break;
            }
            case BipolarSigmoidFunction: {
                output_neurons_function = new BipolarSigmoid();
                break;
            }
        }

        QVector<Neuron*> output_layer;
        QVector<Neuron*> input_layer;

        _neuron_factory = new PerceptronNeuronFactory();
        _training_algorithm = new Backpropagation(this);

        for (int i = 0; i < outputs; i++) {
            output_layer.push_back(_neuron_factory -> CreateOutputNeuron(output_neurons_function));
		}
        _layers.push_back(output_layer);

        for (int i = 0; i < number_of_hidden_layers; i++) {
            QVector<Neuron*> hidden_layer;
            for (int j = 0; j < number_of_neurons_in_hidden_layers; j++ ) {
                Neuron *hidden = _neuron_factory -> CreateHiddenNeuron(_layers[0], output_neurons_function);
                hidden_layer.push_back(hidden);
			}
            _bias_layer.insert(_bias_layer.begin(), _neuron_factory -> CreateInputNeuron(_layers[0], input_neurons_function));
            _layers.insert(_layers.begin(), hidden_layer);

		}

        for (int i = 0; i < inputs; i++) {
            input_layer.push_back(_neuron_factory -> CreateInputNeuron(_layers[0], input_neurons_function));
		}
        _bias_layer.insert(_bias_layer.begin(), _neuron_factory -> CreateInputNeuron(_layers[0], input_neurons_function));
        _layers.insert(_layers.begin(), input_layer);
        _training_algorithm -> WeightsInitialization();
    } else {
        qCritical() << "Error in Neural Network constructor: The number of input and output neurons has to be more than 0!\n";
	}
}


NeuralNetwork::~NeuralNetwork() {
    delete _neuron_factory;
    delete _training_algorithm;

    for (int i = 0; i < _bias_layer.size(); i++) {
        delete _bias_layer[i];
	}

    for (int i = 0; i < _layers.size(); i++) {
        for (int j = 0; j < _layers[i].size(); j++) {
            delete _layers[i].at(j);
		}
	}
}


void NeuralNetwork::set_algorithm(TrainAlgorithm *algorithm) {
    _training_algorithm = algorithm;
}


void NeuralNetwork::set_neuron_factory(NeuronFactory *factory) {
    _neuron_factory = factory;
}


void NeuralNetwork::set_min_mean_squared_error(double error) {
    _min_mean_squared_error = error;
}


int NeuralNetwork::get_inputs() const {
    return _inputs;
}


int NeuralNetwork::get_outputs() const {
    return _outputs;
}


QVector<QVector<Neuron*> > NeuralNetwork::get_layers() const {
    return _layers;
}


double NeuralNetwork::get_min_mean_squared_error() const {
    return _min_mean_squared_error;
}


bool NeuralNetwork::Train(QVector<double>  &data, QVector<int> &target) {
    bool success = true;
    int iteration = 0;
    while(success) {
        iteration++;
        _training_algorithm -> Train(data, target);
        double mse = get_mean_squared_error();
        if (mse < _min_mean_squared_error)
            success = false;
        ResetMSE();
	}
    return success;
}


QVector<int> NeuralNetwork::NetResponse(QVector<double> &data) {
    QVector<int> response;
    if (data.size() != _inputs)
        return response;
    else {
        for (int i = 0; i < GetInputLayer().size(); i++) {
            GetInputLayer().at(i) -> Input(data[i]);
		}
        for (int layers = 0; layers < _layers.size() - 1; layers++) {
            _bias_layer[layers] -> Input(1.0);

            for (int index = 0; index < _layers.at(layers).size(); index++) {
                _layers.at(layers).at(index) -> Fire();
			}
            _bias_layer[layers] -> Fire();
		}

        for (int outputs = 0; outputs < _outputs; outputs++) {
            double result = GetOutputLayer().at(outputs) -> Fire();
            response.push_back(qRound(result));
		}
        ResetCharges();
        return response;
	}
}


void NeuralNetwork::ResetCharges() {
    for (int i = 0; i < _layers.size(); i++) {
        for (int output = 0; output < _layers.at(i).size(); output++)
            _layers.at(i).at(output) -> ResetSumOfCharges();
	}
    for (int i = 0; i < _layers.size() - 1; i++)
            _bias_layer[i] -> ResetSumOfCharges();
}


void NeuralNetwork::UpdateWeights() {
    for (int layer = 0; layer < _layers.size(); layer++) {
        for (int neuron = 0; neuron < _layers[layer].size(); neuron++)
            _layers[layer].at(neuron) -> PerformWeightsUpdating();
	}
}


void NeuralNetwork::ShowNetworkState() {
    for (int layer = 0; layer < _layers.size(); layer++) {
        qWarning() << "Layer index: " << layer << endl;
        for (int neuron = 0; neuron < _layers[layer].size(); neuron++) {
            qWarning() << "  Neuron index: " << neuron << endl;
            _layers[layer].at(neuron) -> ShowNeuronState();
		}
        if (layer < _bias_layer.size()) {
            qWarning() << "  Bias: " << endl;
            _bias_layer[layer] -> ShowNeuronState();
		}
	}
}


QVector<Neuron*> NeuralNetwork::GetLayer(int index) const {
    return _layers[index];
}


int NeuralNetwork::size() const {
    return _layers.size();
}


QVector<Neuron*> NeuralNetwork::GetOutputLayer() const {
    return _layers[_layers.size() - 1];
}


QVector<Neuron*> NeuralNetwork::GetInputLayer() const {
    return _layers[0];
}


QVector<Neuron*> NeuralNetwork::GetBiasLayer() const {
    return _bias_layer;
}


void NeuralNetwork::AddMSE(double value) {
    _mean_squared_error += value;
}


double NeuralNetwork::get_mean_squared_error() const {
    return _mean_squared_error;
}


void NeuralNetwork::ResetMSE() {
    _mean_squared_error = 0.0;
}
