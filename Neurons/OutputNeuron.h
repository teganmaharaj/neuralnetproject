#include "Neuron.h"

#ifndef __OUTPUTNEURON__
#define __OUTPUTNEURON__

class OutputNeuron:public Neuron
{
public:
  OutputNeuron(Neuron&);
  int getIdentifier();
};
#endif
