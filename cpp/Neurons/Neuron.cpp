#include "Neuron.h"
#include "math.h"
#include <iostream>


Neuron::Neuron(): Node()
{
	accumulated    = 0.0f;
        bias           = 0.0f;
        delta	       = 0.0f;
	omega	       = 0.0f;
	connectionsIn  = vector <Connection*>();
	connectionsOut = vector <Connection*>();
}
//Global functions for determining how much of the signal is propogated
float sig(float x)
{
  return 1/(1+exp(-x));
}
float diffsig(float x)
{
  return -(sig(x)*sig(x)-sig(x));
}

bool Neuron::receive(Signal& signal)
{
  //just add the signal to accumulated
  accumulated += signal.get();
  return true;
}
bool Neuron::collect() const
{
  //modify the sum of signals plus a bias based on the sig function
  float strength = sig(accumulated+bias);
  //make a new signal out of it
  Signal sendSignal = Signal(strength);
  //send it to all of this neurons outConnections
  send(sendSignal);
  return true;
}

bool Neuron::send(Signal& outgoing) const
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		Signal s = Signal(outgoing);
		connectionsOut[i]->send(s);
	} 
	return true;
}

void Neuron::reset()
{
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

void Neuron::adjust(char expected)
{
  //modifies the current bias of this neuron based on delta and eta, and then makes all of the neurons connected into it, adjust as well
  bias -= eta * getDelta(expected);
  for(int i=0; i<connectionsIn.size();i++)
  {
    connectionsIn[i]->adjust(expected);
  }
}

float Neuron::getOmega()
{
  //only calculate omega if it is equal to 0, otherwise just return it, this is meant to reduce redundancy
  omega = omega != 0.0f ?omega:sig(accumulated+bias);
  return omega;
}

float Neuron::getDelta(char expected)
{
  //again only caculate delta if it is equal to 0
  if(delta == 0.0f)
  {
    float sum = 0.0f;
    for(int i = 0; i<connectionsOut.size();i++)
    {
      //get the sum of all of the next neurons, modified by that connection's weight
      sum += ((Neuron*)allNeurons[connectionsOut[i]->getTo()])->getDelta(expected) * connectionsOut[i]->getWeight();
    }
    //set delta based on its partial derivative and the sum
    delta = getOmega()*(1-getOmega())*sum;
  }
  return delta;
}
