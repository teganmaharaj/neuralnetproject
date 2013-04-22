#ifndef __OUTPUTNEURON__
#define __OUTPUTNEURON__

#include "Neuron.h"

extern Node ** allNeurons;

class OutputNeuron:public Neuron
{
private:
  int index;
  char identifier;
public:
  OutputNeuron(int, char);

  char getIdentifier(){return identifier;};
  int getIndex(){return index;};

  float getDelta(char);

  friend ofstream& operator<<(ofstream&,OutputNeuron&);

};
#endif
