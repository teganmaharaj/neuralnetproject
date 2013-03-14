#include "InputNeuron.h"


InputNeuron::InputNeuron(Neuron& rhs, int index)
{
   this->index=index;
   for(int i=0;i<rhs.connectionsOut.size();i++)
   {
      this->connectionsOut.push_back(rhs.connectionsOut[i]);
   }
   wasActivated=false;
}


bool InputNeuron::receive(Signal& s){
  for(int i=0;i<connectionsOut.size();i++)
  {
     if (!(connectionsOut[i]->send(s)))
	return false;
  }
  return true;
}
