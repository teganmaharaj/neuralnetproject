#include "Neuron.h"
#include "math.h"
#include <iostream>


Neuron::Neuron(): Node()
{
	wasActivated = false;
	connectionsIn = vector <Connection*>();
	connectionsOut = vector <Connection*>();
}
/*
Neuron::Neuron(vector <*Connection> in, vector <*Connection> out) 
{
	connectionsIn = in;
    connectionsOut = out;
	wasActivated = false;
}
*/
bool Neuron::Node::receive(Signal& signal)
{
  return false;
}
bool Neuron::receive(Signal& signal)
{
	accumulated=(accumulated*counter+signal.get())/++counter;
	float avgStrength = tanh(accumulated);

	if (avgStrength > threshold) 
	{
		Signal sendSignal = Signal(avgStrength);
		send(sendSignal);
		wasActivated = true;
	}
	return true;
}
bool Neuron::Node::send(Signal& outgoing)
{
  return false;
}
bool Neuron::send(Signal& outgoing)
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		connectionsOut[i]->send(Signal(outgoing));
	} 
	return true;
}
void Neuron::Node::reset()
{
}
void Neuron::reset()
{
	wasActivated = false;
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		connectionsOut[i]->reset();
	} 
}


ofstream& operator<<(ofstream& file, Neuron& newneuron)
{
  return file;
}
ifstream& operator>>(ifstream& file, Neuron& newneuron)
{
  return file;
}

void Neuron :: reward(float strength)
{
	for(int i=0; i<connectionsIn.size();i++)
	{
		connectionsIn[i]->reward(strength);
	}
}

void Neuron :: punish(float strength)
{
	for(int i=0; i<connectionsIn.size();i++)
	{
		connectionsIn[i]->punish(strength);
	}
}


