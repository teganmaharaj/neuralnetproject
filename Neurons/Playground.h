#ifndef __PLAYGROUND__
#define __PLAYGROUND__

#include "Neuron.h"
#include "Connection.h"
#include "OutputNeuron.h"

extern Neuron **allNeurons;
extern int netSize;

class Playground
{
public:
  Playground();
  Playground(const Playground& rhs);
  
  void addOutput(int);
  
  vector<OutputNeuron*> olist;

  friend ofstream& operator<<(ofstream& file, Playground p);
};

#endif
