#include "OutputNeuron.h"

OutputNeuron::OutputNeuron(int index, char identifier)
{
   this->index=index;
   this->identifier=identifier;
   wasActivated=false;
}
