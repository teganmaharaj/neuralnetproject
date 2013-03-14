#include "OutputNeuron.h"

OutputNeuron::OutputNeuron(Neuron& rhs, int index, char identifier)
{
   this->index=index;
   this->identifier=identifier;
   for(int i=0;i<rhs.connectionsIn.size();i++)
   {
      this->connectionsIn.push_back(rhs.connectionsIn[i]);
   }
   wasActivated=false;
}
