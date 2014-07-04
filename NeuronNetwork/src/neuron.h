#ifndef NEURON_H_
#define NEURON_H_

#include "neurallink.h"
#include "networkfunction.h"
#include <QVector>
#include <QDebug>
//#include <iostream>

/* Скорость обучения */
const double LEARNING_RATE = 0.01;


class Neuron {
protected:
    NetworkFunction *_network_function;
    /* Входные связи */
    QVector<NeuralLink*> _input_links;
    /* Связи от нейронов */
    QVector<NeuralLink*> _links_to_neurons;
    /* Сумма весов */
    double _sum_of_charges;
public:
    Neuron();
    Neuron(NetworkFunction *function);
    Neuron(QVector<NeuralLink*> links_to_neurons, NetworkFunction *function);
    Neuron(QVector<Neuron *> &neurons_link_to, NetworkFunction *function);
    virtual ~Neuron();

    virtual QVector<NeuralLink*>& get_links_to_neurons() const;
    virtual NeuralLink* at(const int index_of_neural_link);

    virtual void set_link_to_neuron(NeuralLink *link);

    virtual void Input(double input_data);
    virtual double Fire();
    virtual int	get_number_of_links() const;
    virtual double get_sum_of_charges() const;
    virtual void ResetSumOfCharges();
    virtual double Process();
    virtual double Process(double value);
    virtual double Derivative();

    virtual void set_input_link(NeuralLink *link);
    virtual QVector<NeuralLink*> &get_input_links() const;

    virtual double PerformTrainingProcess(double);
    virtual void PerformWeightsUpdating();

    virtual void ShowNeuronState();

};

template <typename T>
class OutputLayerNeuronDecorator : public Neuron<T>
{
public:
						OutputLayerNeuronDecorator( Neuron<T> * inNeuron )		{ mOutputCharge = 0; mNeuron = inNeuron; };
	virtual					~OutputLayerNeuronDecorator( );

	virtual std::vector<NeuralLink<T > *>&	GetLinksToNeurons( )						{ return mNeuron->GetLinksToNeurons( ) ;};
	virtual NeuralLink<T> *			at( const int& inIndexOfNeuralLink )				{ return ( mNeuron->at( inIndexOfNeuralLink ) ) ;};
	virtual void				SetLinkToNeuron( NeuralLink<T> * inNeuralLink )			{ mNeuron->SetLinkToNeuron( inNeuralLink ); };
	virtual double				GetSumOfCharges( )						{ return mNeuron->GetSumOfCharges( ); };

	virtual void				ResetSumOfCharges( )						{ mNeuron->ResetSumOfCharges( ); };
	virtual void				Input( double inInputData )					{ mNeuron->Input( inInputData ); };
	virtual double				Fire( );
	virtual int				GetNumOfLinks( )						{ return mNeuron->GetNumOfLinks( ); };


	virtual double				Process( )							{ return mNeuron->Process( ); };
	virtual double				Process( double inArg )						{ return mNeuron->Process( inArg ); };

	virtual double				Derivative( )							{ return mNeuron->Derivative( ); };

	virtual void				SetInputLink( NeuralLink<T> * inLink )				{ mNeuron->SetInputLink( inLink ); };
	virtual std::vector<NeuralLink<T > *>&	GetInputLink( )							{ return mNeuron->GetInputLink( ); };

	virtual double				PerformTrainingProcess( double inTarget );
	virtual void				PerformWeightsUpdating( );
	virtual void				ShowNeuronState( )						{ mNeuron->ShowNeuronState( ); };
protected:
	double					mOutputCharge;
	Neuron<T> *				mNeuron;

};

template <typename T>
class HiddenLayerNeuronDecorator : public Neuron<T>
{
public:
						HiddenLayerNeuronDecorator( Neuron<T> * inNeuron )		{ mNeuron = inNeuron; };
	virtual					~HiddenLayerNeuronDecorator( );

	virtual std::vector<NeuralLink<T > *>&	GetLinksToNeurons( )						{ return mNeuron->GetLinksToNeurons( ); };
	virtual void				SetLinkToNeuron( NeuralLink<T> * inNeuralLink )			{ mNeuron->SetLinkToNeuron( inNeuralLink ); };
	virtual double				GetSumOfCharges( )						{ return mNeuron->GetSumOfCharges( ) ;};

	virtual void				ResetSumOfCharges( )						{mNeuron->ResetSumOfCharges( ); };
	virtual void				Input( double inInputData )					{ mNeuron->Input( inInputData ); };
	virtual double				Fire( );
	virtual int				GetNumOfLinks( )						{ return mNeuron->GetNumOfLinks( ); };
	virtual NeuralLink<T> *			at( const int& inIndexOfNeuralLink )				{ return ( mNeuron->at( inIndexOfNeuralLink) ); };

	virtual double				Process( )							{ return mNeuron->Process( ); };
	virtual double				Process( double inArg )						{ return mNeuron->Process( inArg ); };

	virtual double				Derivative( )							{ return mNeuron->Derivative( ); };

	virtual void				SetInputLink( NeuralLink<T> * inLink )				{ mNeuron->SetInputLink( inLink ); };
	virtual std::vector<NeuralLink<T > *>&	GetInputLink( )							{ return mNeuron->GetInputLink( ); };

	virtual double				PerformTrainingProcess( double inTarget );
	virtual void				PerformWeightsUpdating( );

	virtual void				ShowNeuronState( )						{ mNeuron->ShowNeuronState( ); };
protected:


	Neuron<T> *				mNeuron;

};


#endif /* NEURON_H_ */
