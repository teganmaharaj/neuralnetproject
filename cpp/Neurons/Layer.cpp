#include "Layer.h"
#include <iostream>
using namespace std;

extern int * shm_onlayer;
extern int * shm_collected;

bool Layer::collect() const
{
  *shm_onlayer=index+1;
  if(next)
  {
    while(*shm_collected<next->length)
    {
      usleep(1000);
    }
    *shm_collected=0;
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
