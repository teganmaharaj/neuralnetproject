#ifndef __INPUTNEURON__
#define __INPUTNEURON__

#include "Neuron.h"

class InputNeuron: public Neuron
{
private:
  int id;
public:
  InputNeuron(Neuron&);
  
  friend ofstream& operator<<(ofstream&,InputNeuron&);
};
#endif
