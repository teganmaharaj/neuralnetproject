#include "Layer.h"
#include <iostream>
using namespace std;
bool Layer::collect() const
{
  for(int m=base;m<base+length;m++)
  {
    //for all the neurons in this layer's juristiction, call collect(which sends a signal to that neuron's outConnections, to the next layer)
    ((Neuron*)allNeurons[m])->collect();
  }
  //if this layer has a next layer that it knows about, tell it to collect.
  if(next)
  {
    next->collect();
  }
}

void Layer::adjust(char expected)
{
  for(int i=base;i<base+length;i++)
  {
    //for all the neurons in this layer's juristiction call adjust(which requires the getOmega from the next layer, so this too sends a signal forward, in a way)
    ((Neuron*)allNeurons[i])->adjust(expected);
  }
  if(next)
  {
    next->adjust(expected);
  }
}
