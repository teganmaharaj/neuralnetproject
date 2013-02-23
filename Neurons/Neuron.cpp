#include "Neuron.h"
#include <Math.h>


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
	}
	return true;
}

void Neuron::send(Signal& outgoing)
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		connectionsOut[i]->send(outgoing);
	} 
}

void Neuron::reset()
{
	isActivated = false;
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
