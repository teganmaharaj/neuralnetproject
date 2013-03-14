#ifndef __PLAYGROUND__
#define __PLAYGROUND__

#include "Neuron.h"
#include "Connection.h"
#include "OutputNeuron.h"

extern Node **allNeurons;
extern int netSize;

class Playground
{
public:
  Playground();
  Playground(const Playground& rhs);
  void addOutput(int,char);
  char land(char);
  
  

  friend ofstream& operator<<(ofstream& file, Playground p);
private:
  vector<OutputNeuron*> olist;
};

#endif
