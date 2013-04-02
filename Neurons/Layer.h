
#include "Neuron.h"
#ifndef __LAYER__
#define __LAYER__

extern Node ** allNeurons;

class Layer
{
public:
  int base;
  int length;
  Layer * next;

public:
  Layer(int b, int l){base = b; length = l;}
  bool collect() const;
  void adjust(char);

  void setNext(Layer*n){next = n;}
  void setBase(int b){base = b;}
  void setLength(int l){length = l;}
};

#endif
