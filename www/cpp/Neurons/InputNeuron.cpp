#include "InputNeuron.h"
#include <iostream>
using namespace std;

InputNeuron::InputNeuron(int index)
{
   bias = ((Neuron*)allNeurons[index])->bias;
   delete allNeurons[index];
   this->index=index;
}


bool InputNeuron::send(Signal& s) const
{
  for(int i=0;i<connectionsOut.size();i++)
  {
     Signal outgoing = Signal(accumulated);
     if (!(connectionsOut[i]->send(outgoing)))
	return false;
  }
//  cout << "SIZE" << connectionsOut.size() << endl;
  return true;
}
