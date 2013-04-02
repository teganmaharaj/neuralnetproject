#include "Layer.h"
#include <iostream>
using namespace std;
bool Layer::collect() const
{
  cout << "collecting myself before the battle" << endl;
  cout << "base: " << base << " length " << length << endl;
  for(int m=base;m<base+length;m++)
  {
    cout << "neuron: " << m << " sum = " << ((Neuron*)allNeurons[m])->getAccumulated() << endl;
    ((Neuron*)allNeurons[m])->collect();
  }
  cout << "start next" << endl;
  if(next)
  {
    next->collect();
  }
}

void Layer::adjust(char expected)
{
  cout << "deploy parachute!" << endl;
  cout << "base: " << base << " length " << length << endl;
  for(int i=base;i<base+length;i++)
  {
    ((Neuron*)allNeurons[i])->adjust(expected);
  }
  if(next)
  {
    next->adjust(expected);
  }
}
