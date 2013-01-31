#ifndef __NEURON__
#define __NEURON__

#include "Signal.h"
#include <fstream>

using namespace std;

/*
* Neurons are the main data type of the neural net
* They must receive and send signals from other neurals
* They must activate when excited, based on a function (tranh for example)
* They must they must modify their outgoing weights based on input by the Playground
* They can delete connections that drop below a threshold(become close to 0)
*/
class Neuron
{
public:
  void reset();
  bool receive(Signal&);
  friend ofstream& operator<<(ofstream&, Neuron&);
  friend ifstream& operator>>(ifstream&, Neuron&);
};

#endif
