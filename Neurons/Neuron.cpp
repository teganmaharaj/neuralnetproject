#include "Neuron.h"
void Neuron::reset()
{
}

bool Neuron::receive(Signal&)
{
return false;
}

ofstream& operator<<(ofstream& file, Neuron& newneuron)
{
  return file;
}
ifstream& operator>>(ifstream& file, Neuron& newneuron)
{
  return file;
}
