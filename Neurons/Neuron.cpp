#include "Neuron.h"

void Neuron::reset()
{
}

bool Neuron::receive(Signal& incoming)
{
	totalStrength = 0;
	for (int i=0; i<connectionsIn.size(); i++) 
	{
		totalStrength = totalStrength + connectionsIn[i].getActivation();
	} 

	avgStrength = Math.tanh(totalStrength/connectionsIn.size());

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
		connectionsOut[i].send(outgoing);
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
