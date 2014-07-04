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
        neurons_link_to[i] -> SetInputLink(link);
	}

}


Neuron<T>::~Neuron() {

}


QVector<NeuralLink*>& Neuron::get_links_to_neurons() const {
    return _links_to_neurons;
}


NeuralLink* Neuron::at(const int index_of_neural_link) {
    _links_to_neurons.at(index_of_neural_link);
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

        double delta_weight = current_link -> get_weight();
        double	delta_charge = _sum_of_charges;
        double 	delta_x_i = (_network_function -> Process(delta_charge));
        double 	delta_output = delta_x_i * delta_weight;

        current_link -> set_last_translated_signal(delta_x_i);
        current_neuron_linked_to -> Input(delta_output);
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


QVector<NeuralLink*> Neuron::get_inputlinks() const {
    return _input_links;
}


double Neuron::PerformTrainingProcess(double) {
    return 0;
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



/*** http://habrahabr.ru/post/198268/ ***/

template <typename T>
OutputLayerNeuronDecorator<T>::~OutputLayerNeuronDecorator()
{
	delete mNeuron;
}

template <typename T>
HiddenLayerNeuronDecorator<T>::~HiddenLayerNeuronDecorator()
{
	delete mNeuron;
}


template <typename T>
double HiddenLayerNeuronDecorator<T>::Fire()
{
	/*
	 * 		Hidden unit applies its activation function to compute its output signal
	 * 		and sends this signal to all units in the layer above (output units).
	*/

	for(int iLink = 0; iLink < this->GetNumOfLinks(); iLink++){

		NeuralLink<T> * pCurrentLink = mNeuron->at(iLink);
		Neuron<T> * pCurrentNeuronLinkedTo = pCurrentLink->GetNeuronLinkedTo();

		const double dWeight = mNeuron->at(iLink)->GetWeight();
		double	dCharge = mNeuron->GetSumOfCharges();
		double	dZj = (mNeuron->Process(dCharge));
		double 	dOutput = dZj*dWeight;

		pCurrentLink->SetLastTranslatedSignal(dZj);

		pCurrentNeuronLinkedTo->Input( dOutput );

		//std::cout << "Link: " << iLink << ", " << "Hidden Neuron fired: " << dOutput << " as func of: " << dCharge << " * " << dWeight << std::endl;
	}

	return mNeuron->GetSumOfCharges();
}

template <typename T>
double OutputLayerNeuronDecorator<T>::Fire()
{

	//double temp = mNeuron->GetSumOfCharges();
	double output = this->Process();
	mOutputCharge = output;
	//std::cout << "Output Neuron fired: " << output << " as func of: " << temp << std::endl;
	return output;

};

template <typename T>
double Neuron<T>::Fire()
{
	for(int iLink = 0; iLink < this->GetNumOfLinks(); iLink++){
		NeuralLink<T> * pCurrentLink = mLinksToNeurons[iLink];
		Neuron<T> * pCurrentNeuronLinkedTo = pCurrentLink->GetNeuronLinkedTo();

		const double dWeight = pCurrentLink->GetWeight();
		double	dCharge = mSumOfCharges;
		double 	dXi =  (mNetFunc->Process(dCharge));
		double 	dOutput = dXi*dWeight;

		pCurrentLink->SetLastTranslatedSignal(dXi);
		pCurrentNeuronLinkedTo->Input( dOutput );
		//std::cout << "Link: " << iLink << ", Neuron fired: " << dOutput << " as func of: " << dCharge << " * " << dWeight << std::endl;
		//mLinksToNeurons[iLink]->GetNeuronLinkedTo()->Input(mNetFunc->Process(mSumOfCharges*mLinksToNeurons[iLink]->GetWeight()));
	}
	//mSumOfCharges = 0;
	return mSumOfCharges;
}

template <typename T>
double	Neuron<T>::GetSumOfCharges()
{

	return mSumOfCharges;
}






template <typename T>
double HiddenLayerNeuronDecorator<T>::PerformTrainingProcess(double inTarget)
{

	/*
	 * 		Hidden unit sums its delta inputs from units in the layer above
	*/
	double dDeltaInputs = 0;
	for(int iOutputLink = 0; iOutputLink < (this->GetNumOfLinks()); iOutputLink++){
			NeuralLink<T> * pOutputLink = (this->GetLinksToNeurons()).at(iOutputLink);
			double dErrorInformationTerm = pOutputLink->GetErrorInFormationTerm();
			double dWeight = pOutputLink->GetWeight();
			dDeltaInputs = dDeltaInputs + (dWeight*dErrorInformationTerm);
	}

/*	for(int iOutputLink = 0; iOutputLink < (this->GetNumOfLinks()); iOutputLink++){
			NeuralLink * pOutputLink = (this->GetLinksToNeurons()).at(iOutputLink);
			pOutputLink->UpdateWeight();
	}*/

	double dErrorInformationTermj = dDeltaInputs * (this->Derivative());
	//std::cout << "dErrorInformationTermjHidden: " << dErrorInformationTermj << " as: " << dDeltaInputs << " * " << this->Derivative() << " .Derivative of:  " << mNeuron->GetSumOfCharges()<< std::endl;
	//std::cin.get();
	/*
	 * 		For every link to that hidden neuron, (inputLinks) calculate its weight correction term
	 * 		and update the link with it.
	*/
	for(unsigned int iInputLink = 0; iInputLink < (this->GetInputLink()).size(); iInputLink++){
		NeuralLink<T> * pInputLink = (this->GetInputLink()).at(iInputLink);
		double Xi = pInputLink->GetLastTranslatedSignal();
		double dWeightCorrectionTerm = Xi*dErrorInformationTermj;
		//std::cout << "dWeightCorrectionTerm: " << dWeightCorrectionTerm << std::endl;
		pInputLink->SetWeightCorrectionTerm(LearningRate*dWeightCorrectionTerm);


		/*
		 * 		Then hidden unit has to tell the input neurons the value of it ErrorInformationTerm, so we are setting its value
		 * 		in the link object.
		 */

		pInputLink->SetErrorInFormationTerm(dErrorInformationTermj);
	}
	return 0;
}

template <typename T>
double OutputLayerNeuronDecorator<T>::PerformTrainingProcess(double inTarget)
{
	double res;
	double dErrorInformationTerm = (inTarget - mOutputCharge) * mNeuron->Derivative();
	res = pow(inTarget - mOutputCharge,2);
	//std::cout << "dErrorInformationTermOutput: " << dErrorInformationTerm << " as: " << "(" << inTarget << " - " << mOutputCharge << ")" << " * " << mNeuron->Derivative() << " .Derivative of:  " << mNeuron->GetSumOfCharges()<< std::endl;
	//std::cin.get();

	/*
	 * 		For every link to that output, (inputLinks) calculate its weight correction term
	 * 		and update the link with it.
	*/
	for(unsigned int iInputLink = 0; iInputLink < (this->GetInputLink()).size(); iInputLink++){
		NeuralLink<T> * pInputLink = (this->GetInputLink()).at(iInputLink);
		double Zj = pInputLink->GetLastTranslatedSignal();
		double dWeightCorrectionTerm = Zj*dErrorInformationTerm;
		//std::cout << "dWeightCorrectionTerm: " << dWeightCorrectionTerm << std::endl;
		pInputLink->SetWeightCorrectionTerm(LearningRate*dWeightCorrectionTerm);


		/*
		 * 		Then output unit has to tell the hidden neurons the value of it ErrorInformationTerm, so we are setting its value
		 * 		in the link object.
		 */

		pInputLink->SetErrorInFormationTerm(dErrorInformationTerm);
	}


	return res;
}



template <typename T>
void HiddenLayerNeuronDecorator<T>::PerformWeightsUpdating()
{
	for(unsigned int iInputLink = 0; iInputLink < (this->GetInputLink()).size(); iInputLink++){
		NeuralLink<T> * pInputLink = (this->GetInputLink()).at(iInputLink);

		pInputLink->UpdateWeight();
		//std::cout<<"";
	}
}

template <typename T>
void OutputLayerNeuronDecorator<T>::PerformWeightsUpdating()
{
	for(unsigned int iInputLink = 0; iInputLink < (this->GetInputLink()).size(); iInputLink++){
		NeuralLink<T> * pInputLink = (this->GetInputLink()).at(iInputLink);

		pInputLink->UpdateWeight();
		//std::cout<<"";
	}
}



template class Neuron<double>;
template class Neuron<float>;
template class Neuron<int>;

template class OutputLayerNeuronDecorator<double>;
template class OutputLayerNeuronDecorator<float>;
template class OutputLayerNeuronDecorator<int>;

template class HiddenLayerNeuronDecorator<double>;
template class HiddenLayerNeuronDecorator<float>;
template class HiddenLayerNeuronDecorator<int>;
