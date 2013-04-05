#include "OutputNeuron.h"
#include <iostream>
using namespace std;

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
//    cout << "hello " << expected << "==" << identifier << (expected == identifier) << "||";
    float myExpected = expected == identifier ? 1.0f : 0.0f;
    delta = getOmega()*(1-getOmega())*(getOmega()-(myExpected));
  }
  return delta;
}

