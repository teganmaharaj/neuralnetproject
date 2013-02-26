#ifndef __OUTPUTNEURON__
#define __OUTPUTNEURON__

#include "Neuron.h"

class OutputNeuron:public Neuron
{
private:
  int id;
public:
  OutputNeuron(Neuron&);
  int getIdentifier();

  
  friend ofstream& operator<<(ofstream&,OutputNeuron&);

};
#endif
