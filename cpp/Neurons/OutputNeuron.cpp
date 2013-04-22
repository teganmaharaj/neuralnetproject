#include "OutputNeuron.h"
#include <iostream>
using namespace std;

OutputNeuron::OutputNeuron(int index, char identifier)
{
//record the bias of the neuron this neuron is replacing
   bias = ((Neuron*)allNeurons[index])->bias;
//delete that neuron
   delete allNeurons[index];
//set the index and indetifier of this neuron
   this->index=index;
   this->identifier=identifier;
//note that allNeurons[index] will receive this newly created object
}

//this is the special getDelta method that only output Neurons have
//it is special because output neurons do not rely on the "next" neuron layer, because they are the last layer
float OutputNeuron::getDelta(char expected)
{
  if(delta == 0.0f)
  {
//the expected parameter is the character which the trainer is saying should be the response of the neural net.
//If this is the output neuron that represents that neuron, it's result should be 1(though it never will be fully)
//Otherwise, if this neuron is the neuron that represents another output other than the current test, then it should be outputting a 0
    float myExpected = expected == identifier ? 1.0f : 0.0f;
//this is the formula for calculating the delta of output neurons
    delta = getOmega()*(1-getOmega())*(getOmega()-(myExpected));
  }
  return delta;
}

