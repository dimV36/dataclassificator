/*
 * NeuralNetwork.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: cheryuri
 */


#include "NeuralNetworks/NeuralNetwork.h"

template <typename T>
NeuralNetwork<T>::NeuralNetwork( const int& inInputs, const int& inOutputs, const int& inNumOfHiddenLayers, const int& inNumOfNeuronsInHiddenLayers, const char * inTypeOfNeuralNetwork )
{
	/*
	 * 		Protection against the fools.
	 * 		The neural net needs at least 1 input neuron and 1 output.
	*/

	if(inInputs > 0 && inOutputs > 0){

		mMinMSE			  = 0.01;
		mMeanSquaredError = 0;
		mInputs 		  =	inInputs;
		mOutputs 		  = inOutputs;
		mHidden 		  = inNumOfNeuronsInHiddenLayers;

		/*
		 *		Network function's declarations for input and output neurons.
		*/

		NetworkFunction * OutputNeuronsFunc;
		NetworkFunction * InputNeuronsFunc;

		/*
		 *		At least two layers require - input and output;
		*/

		std::vector<Neuron<T > *> outputLayer;
		std::vector<Neuron<T > *> inputLayer;

		/*
		 *		This block of strcmps decides what training algorithm and neuron factory we should use as well as what
		 *		network function every node will have.
		*/

		if( strcmp( inTypeOfNeuralNetwork, "MultiLayerPerceptron" ) == 0){
			mNeuronFactory = new PerceptronNeuronFactory<T>;
			mTrainingAlgoritm = new Backpropagation<T>(this);

			OutputNeuronsFunc = new BipolarSigmoid;
			InputNeuronsFunc = new Linear;

		}

		/*
		 * 		Output layers creation
		*/

		for(int iNumOfOutputs = 0; iNumOfOutputs < inOutputs; iNumOfOutputs++){
			outputLayer.push_back( mNeuronFactory->CreateOutputNeuron(OutputNeuronsFunc) );
		}
		mLayers.push_back(outputLayer);

		/*
		 * 		Hidden layers creation
		*/

		for(int i = 0; i < inNumOfHiddenLayers; i++){
			std::vector<Neuron<T > *> HiddenLayer;
			for(int j = 0; j < inNumOfNeuronsInHiddenLayers; j++ ){
				Neuron<T> * hidden = mNeuronFactory->CreateHiddenNeuron(mLayers[0], OutputNeuronsFunc);
				HiddenLayer.push_back(hidden);
			}
			mBiasLayer.insert(mBiasLayer.begin(),mNeuronFactory->CreateInputNeuron(mLayers[0], InputNeuronsFunc));
			mLayers.insert(mLayers.begin(),HiddenLayer);

		}

		/*
		 *		Input layers creation
		*/

		for(int iNumOfInputs = 0; iNumOfInputs < inInputs; iNumOfInputs++){
			inputLayer.push_back(mNeuronFactory->CreateInputNeuron(mLayers[0], InputNeuronsFunc));
		}
		mBiasLayer.insert(mBiasLayer.begin(),mNeuronFactory->CreateInputNeuron(mLayers[0],InputNeuronsFunc));
		mLayers.insert(mLayers.begin(),inputLayer);

		mTrainingAlgoritm->WeightsInitialization();
	}
	else{
		std::cout << "Error in Neural Network constructor: The number of input and output neurons has to be more than 0!\n";
	}
}

template <typename T>
NeuralNetwork<T>::~NeuralNetwork()
{
	delete mNeuronFactory;
	delete mTrainingAlgoritm;

	for( unsigned int uNumOfBiases = 0; uNumOfBiases < mBiasLayer.size(); uNumOfBiases++ ){
		delete mBiasLayer[ uNumOfBiases ];
	}

	for( unsigned int uNumOfLayers = 0; uNumOfLayers < mLayers.size(); uNumOfLayers++){
		for( unsigned int uNumOfNeurons = 0; uNumOfNeurons < mLayers[uNumOfLayers].size(); uNumOfNeurons++ ){
			delete mLayers[ uNumOfLayers ].at( uNumOfNeurons );
		}
	}

}

template <typename T>
bool NeuralNetwork<T>::Train( const std::vector<std::vector<T > >& inData, const std::vector<std::vector<T > >& inTarget )
{
	bool trues = true;
	int iIteration = 0;
	while(trues){
		iIteration++;
		for(int i = 0; i < inData.size(); i++){
			mTrainingAlgoritm->Train( inData[i], inTarget[i] );
		}
		double MSE = this->GetMSE();
		if( MSE < mMinMSE){
			std::cout << "At " << iIteration << " iteration MSE: " << MSE << " was achieved\n";
			trues = false;
		}
		this->ResetMSE();
	}
	//return mTrainingAlgoritm->Train( inData,inTarget);
	return trues;
}

template <typename T>
std::vector<int> NeuralNetwork<T>::GetNetResponse( const std::vector<T>& inData )
{
	std::vector<int> netResponse;
	if(inData.size() != mInputs){
		std::cout << "Input data dimensions are wrong, expected: " << mInputs << " elements\n";
		return netResponse;
	}
	else{
		for(unsigned int indexOfData = 0; indexOfData < this->GetInputLayer().size(); indexOfData++){
			this->GetInputLayer().at(indexOfData)->Input(inData[indexOfData]);
		}

		for(unsigned int numOfLayers = 0; numOfLayers < mLayers.size() - 1; numOfLayers++){
			mBiasLayer[numOfLayers]->Input(1.0);

			for(unsigned int indexOfData = 0; indexOfData < mLayers.at(numOfLayers).size(); indexOfData++){
				mLayers.at(numOfLayers).at(indexOfData)->Fire();
			}

			mBiasLayer[numOfLayers]->Fire();
		}

		std::cout << "Net response is: { ";
		for(unsigned int indexOfOutputElements = 0; indexOfOutputElements < mOutputs; indexOfOutputElements++){

			/*
			 * 		For every neuron in output layer, make it fire its sum of charges;
			 */

			double res = this->GetOutputLayer().at(indexOfOutputElements)->Fire();

			std::cout << "res: " << res << std::endl;


		}
		std::cout << " } \n";
		this->ResetCharges();
		return netResponse;

	}



}

template <typename T>
void NeuralNetwork<T>::ResetCharges()
{
	for(unsigned int i = 0; i < mLayers.size(); i++ ){
		for(unsigned int indexOfOutputElements = 0; indexOfOutputElements < mLayers.at(i).size(); indexOfOutputElements++){
			mLayers.at(i).at(indexOfOutputElements)->ResetSumOfCharges();


		}
		//mBiasLayer[i]->ResetSumOfCharges();
	}
	for(unsigned int i = 0; i < mLayers.size()-1; i++ ){
			mBiasLayer[i]->ResetSumOfCharges();
	}

}

template <typename T>
void NeuralNetwork<T>::UpdateWeights()
{
	for(unsigned int indOfLayer = 0; indOfLayer < mLayers.size(); indOfLayer++){
		for(unsigned int indOfNeuron = 0; indOfNeuron < mLayers[indOfLayer].size(); indOfNeuron++){
			mLayers[indOfLayer].at(indOfNeuron)->PerformWeightsUpdating();
		}
	}
}

template <typename T>
void NeuralNetwork<T>::ShowNetworkState()
{
	std::cout << std::endl;
	for(unsigned int indOfLayer = 0; indOfLayer < mLayers.size(); indOfLayer++){
		std::cout << "Layer index: " << indOfLayer << std::endl;
		for(unsigned int indOfNeuron = 0; indOfNeuron < mLayers[indOfLayer].size(); indOfNeuron++){
			std::cout << "  Neuron index: " << indOfNeuron << std::endl;
			mLayers[indOfLayer].at(indOfNeuron)->ShowNeuronState();
		}
		if(indOfLayer < mBiasLayer.size()){
			std::cout << "  Bias: " << std::endl;
			mBiasLayer[indOfLayer]->ShowNeuronState();
		}
	}
}

template class NeuralNetwork<double>;
template class NeuralNetwork<float>;
template class NeuralNetwork<int>;
