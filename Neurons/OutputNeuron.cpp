#include "OutputNeuron.h"

OutputNeuron::OutputNeuron(int index, char identifier)
{
   bias = ((Neuron*)allNeurons[index])->bias;
   delete allNeurons[index];
   this->index=index;
   this->identifier=identifier;
}

float OutputNeuron::getDelta(char expected)
{
  if(delta == 0.0f)
  {
    float myExpected = expected == identifier ? ((int)expected-48) : -1.0f;
    delta = getOmega()*(1-getOmega())*(getOmega()-myExpected);
  }
  return delta;
}

