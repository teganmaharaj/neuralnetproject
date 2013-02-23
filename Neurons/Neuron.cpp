#include "Neuron.h"
#include <Math.h>

Neuron::Neuron()
{
	wasActivated = false;
	connectionsIn = vector <*Connection>();
	connectionsOut = vector <*Connection>();
}
/*
Neuron::Neuron(vector <*Connection> in, vector <*Connection> out) 
{
	connectionsIn = in;
    connectionsOut = out;
	wasActivated = false;
}
*/
bool Neuron::receive()
{
	totalStrength = 0;
	for (int i=0; i<connectionsIn.size(); i++) 
	{
		totalStrength = totalStrength + connectionsIn[i]->getActivation();
	} 
	avgStrength = tanh(totalStrength/connectionsIn.size());

	if (avgStrength > threshold) 
	{
		sendSignal = Signal(avgStrength);
		send(sendSignal);
		wasActivated = true;
	}
	return true;
}

bool Neuron::send(Signal& outgoing)
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		connectionsOut[i]->send(outgoing);
	} 
	return true;
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
