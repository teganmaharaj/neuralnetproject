#ifndef __PLAYGROUND__
#define __PLAYGROUND__

#include "Neuron.h"
#include "Connection.h"
#include "OutputNeuron.h"
#include "Layer.h"

extern Node **allNeurons;
extern int neuralNetSize;

class Playground: public Layer
{
public:
  Playground();
  void addOutput(int,char);

  float getOmega(char);
  
  bool collect() const;
  void start();

  friend ofstream& operator<<(ofstream& file, Playground& p);
};

#endif
