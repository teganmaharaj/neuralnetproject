#ifndef __INPUTNEURON__
#define __INPUTNEURON__

#include "Neuron.h"

extern Node ** allNeurons;

/*
Input neurons are where the signal starts its propogration through the neural net and as such, they do not apply the transfer function(sig) to the outgoing signal
*/
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
