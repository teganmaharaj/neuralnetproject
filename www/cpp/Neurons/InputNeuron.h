#ifndef __INPUTNEURON__
#define __INPUTNEURON__

#include "Neuron.h"

extern Node ** allNeurons;

class InputNeuron: public Neuron
{
private:
  int index;
public:
  InputNeuron(int);
  
  bool send(Signal&) const;
  
  friend ofstream& operator<<(ofstream&,InputNeuron&);
};
#endif
