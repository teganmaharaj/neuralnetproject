#ifndef __OUTPUTNEURON__
#define __OUTPUTNEURON__

#include "Neuron.h"

class OutputNeuron:public Neuron
{
public:
  OutputNeuron(Neuron&);
  int getIdentifier();
};
#endif
