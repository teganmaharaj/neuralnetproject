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
bool Neuron::Node::receive(Signal& signal)
{
  return false;
}

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
  accumulated += signal.get();
  return true;
}
bool Neuron::collect() const
{
  float strength = sig(accumulated+bias);
  Signal sendSignal = Signal(strength);
  send(sendSignal);
  return true;
}
bool Neuron::Node::send(Signal& outgoing) const
{
  return false;
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
void Neuron::Node::reset()
{
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
//  cout << "allo, i am a neuron" << endl;
  bias -= eta * getDelta(expected);
  for(int i=0; i<connectionsIn.size();i++)
  {
    connectionsIn[i]->adjust(expected);
  }
}

float Neuron::Node::getOmega()
{
  return 0.0f;
}
float Neuron::Node::getDelta(char expected)
{
  return 0.0f;
}

float Neuron::getOmega()
{
  omega = omega != 0.0f ?omega:sig(accumulated+bias);
  return omega;
}

float Neuron::getDelta(char expected)
{
  //cout << "I wish to calculate my delta" << endl;
  if(delta == 0.0f)
  {
    float sum = 0.0f;
    for(int i = 0; i<connectionsOut.size();i++)
    {
      sum += ((Neuron*)allNeurons[connectionsOut[i]->getTo()])->getDelta(expected) * connectionsOut[i]->getWeight();
    }
    delta = getOmega()*(1-getOmega())*sum;
  }
  //cout << "I have calculated my delta to be: " << delta << endl;
  return delta;
}
