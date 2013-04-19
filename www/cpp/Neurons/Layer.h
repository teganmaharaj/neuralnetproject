
#include "Neuron.h"
#ifndef __LAYER__
#define __LAYER__

extern Node ** allNeurons;

/*
Layer is the class that is needed to make the activations of the neural net a breadth first ordering
it works by preforming collect on all its neurons, which sends a receive signal to the subsequence layer, but does not propograte the signal further.
The next layer is then prompted to collect its results, and so on

the same concept is used for adjust

keep in mind that both the brain and the playground are layers, just with extra functionality.
The hidden layers have nothing special so they do not have a special class.
*/

class Layer
{
public:
  int base;
  int length;
  Layer * next;

public:
  //CONSTRUCTOR
  Layer(int b, int l){base = b; length = l;}
  //for the forward propegation of signals
  bool collect() const;
  //for the so called 'back propogation' learning strategy
  void adjust(char);

  //SETTERS
  void setNext(Layer*n){next = n;}
  void setBase(int b){base = b;}
  void setLength(int l){length = l;}
};

#endif
