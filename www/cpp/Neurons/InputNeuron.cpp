#include "InputNeuron.h"
#include <iostream>
using namespace std;

InputNeuron::InputNeuron(int index)
{
//copy the bias of the neuron who's index you are replacing
   bias = ((Neuron*)allNeurons[index])->bias;
//delete that neuron
   delete allNeurons[index];
//set your index to that neuron's index
   this->index=index;
//this constructor will return into the allNeurons[i]
}


bool InputNeuron::send(Signal& s) const
{
//it was very important that this method be overwritten only because we do not want the accumulated signal to be modified yet, send should send the unadulterated signal(not apply sig) to it's connections out
  for(int i=0;i<connectionsOut.size();i++)
  {
     Signal outgoing = Signal(accumulated);
     if (!(connectionsOut[i]->send(outgoing)))
	return false;
  }
  return true;
}
