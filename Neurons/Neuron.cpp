#include "Neuron.h"
#include "math.h"
#include <iostream>


Neuron::Neuron(): Node()
{
	counter = 0;
	accumulated = 1.0f;
	wasActivated = false;
	connectionsIn = vector <Connection*>();
	connectionsOut = vector <Connection*>();
}
/*
Neuron::Neuron(Node& node)
{
	counter = 0;
        accumulated = 0.0f;
        wasActivated = false;
        connectionsIn = vector <Connection*>();
        connectionsOut = vector <Connection*>();
}*/
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
//	cout << signal.get() << "//";
	accumulated=(accumulated*counter+signal.get())/++counter;
//        cout << accumulated << "//";
	float avgStrength = tanh(accumulated);
//	cout << avgStrength << ">>" << counter<< "//";
	if (avgStrength > threshold)
	{
//		cout << "FIRE" << endl;
		Signal sendSignal = Signal(1.0f);
		send(sendSignal);
		wasActivated = true;
                accumulated=1.0f;
//		counter = 0;
	}
	return true;
}
bool Neuron::Node::send(Signal& outgoing)
{
  return false;
}
void Neuron::Node::punish(float penalty)
{
}
void Neuron::Node::reward(float candy)
{
}

bool Neuron::send(Signal& outgoing)
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


