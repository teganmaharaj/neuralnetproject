#include "InputNeuron.h"
#include <iostream>
using namespace std;

InputNeuron::InputNeuron(int index)
{
   this->index=index;
   wasActivated=false;
}


bool InputNeuron::receive(Signal& s){
  for(int i=0;i<connectionsOut.size();i++)
  {
     cout << "i"	 << endl;
     if (!(connectionsOut[i]->send(s)))
	return false;
  }
  cout << "SIZE" << connectionsOut.size() << endl;
  return true;
}
