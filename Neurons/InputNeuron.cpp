#include "InputNeuron.h"
#include <iostream>
using namespace std;

InputNeuron::InputNeuron(int index)
{
   bias = ((Neuron*)allNeurons[index])->bias;
   delete allNeurons[index];
   this->index=index;
}


bool InputNeuron::send(Signal& s)
{
  for(int i=0;i<connectionsOut.size();i++)
  {
     //cout << "i:" <<  	 << endl;
     Signal outgoing = Signal(accumulated);
     if (!(connectionsOut[i]->send(s)))
	return false;
  }
//  cout << "SIZE" << connectionsOut.size() << endl;
  return true;
}
