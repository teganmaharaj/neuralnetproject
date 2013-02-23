#include "Neuron.h"

void Neuron::reset()
{
}

bool Neuron::receive(Signal& input)
{
	totalStrength = 0;
	for (int i=0; i<connectionsIn.size(); i++) {
		totalStrength = totalStrength + connectionsIn[i].getActivation();
	} 

	avgStrength = Math.tanh(totalStrength/connectionsIn.size());

	if (avgStrength > threshold) {
		send(input);
	}
	return true;
}

void Neuron::send() 
{
	for (int i=0; i<connectionsOut.size(); i++) {
		connectionsOut[i].;
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
