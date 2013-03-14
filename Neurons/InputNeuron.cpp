#include "InputNeuron.h"


InputNeuron::InputNeuron(int index)
{
   this->index=index;
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
