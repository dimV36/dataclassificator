/*
 * NeuronFactory.h
 *
 *  Created on: Sep 25, 2013
 *      Author: cheryuri
 */

#ifndef NEURONFACTORY_H_
#define NEURONFACTORY_H_

#include "Neuron.h"

template <typename T>
class NeuronFactory
{
public:
					NeuronFactory(){};
	virtual				~NeuronFactory(){};
	virtual Neuron<T> *		CreateInputNeuron( std::vector<Neuron<T > *>& inNeuronsLinkTo, NetworkFunction * inNetFunc ) = 0;
	virtual Neuron<T> *		CreateOutputNeuron( NetworkFunction * inNetFunc ) = 0;
	virtual Neuron<T> *		CreateHiddenNeuron( std::vector<Neuron<T > *>& inNeuronsLinkTo, NetworkFunction * inNetFunc ) = 0;

};

template <typename T>
class PerceptronNeuronFactory : public NeuronFactory<T>
{
public:
				PerceptronNeuronFactory(){};
	virtual			~PerceptronNeuronFactory(){};
	virtual Neuron<T> *	CreateInputNeuron( std::vector<Neuron<T > *>& inNeuronsLinkTo, NetworkFunction * inNetFunc ){ return new Neuron<T>( inNeuronsLinkTo, inNetFunc ); };
	virtual Neuron<T> * 	CreateOutputNeuron( NetworkFunction * inNetFunc ){ return new OutputLayerNeuronDecorator<T>( new Neuron<T>( inNetFunc ) ); };
	virtual Neuron<T> * 	CreateHiddenNeuron( std::vector<Neuron<T > *>& inNeuronsLinkTo, NetworkFunction * inNetFunc ){ return new HiddenLayerNeuronDecorator<T>( new Neuron<T>( inNeuronsLinkTo, inNetFunc ) ); };
};


#endif /* NEURONFACTORY_H_ */
