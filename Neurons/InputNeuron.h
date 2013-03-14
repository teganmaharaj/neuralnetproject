#ifndef __INPUTNEURON__
#define __INPUTNEURON__

#include "Neuron.h"

class InputNeuron: public Neuron
{
private:
  int index;
public:
  InputNeuron(Neuron&, int);
  
  bool receive(Signal&);
  
  friend ofstream& operator<<(ofstream&,InputNeuron&);
};
#endif
