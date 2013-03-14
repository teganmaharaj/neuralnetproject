#ifndef __OUTPUTNEURON__
#define __OUTPUTNEURON__

#include "Neuron.h"

class OutputNeuron:public Neuron
{
private:
  int index;
  char identifier;
public:
  OutputNeuron(Neuron&, int, char);

  char getIdentifier(){return identifier;};
  int getIndex(){return index;};

  friend ofstream& operator<<(ofstream&,OutputNeuron&);

};
#endif
