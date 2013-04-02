#ifndef __PLAYGROUND__
#define __PLAYGROUND__

#include "Neuron.h"
#include "Connection.h"
#include "OutputNeuron.h"
#include "Layer.h"

extern Node **allNeurons;
extern int netSize;

class Playground: public Layer
{
public:
  Playground();
  void addOutput(int,char);

  float getOmega(char);

  friend ofstream& operator<<(ofstream& file, Playground& p);
};

#endif
