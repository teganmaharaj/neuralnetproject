#ifndef __PLAYGROUND__
#define __PLAYGROUND__

#include "Connection.h"
#include "OutputNeuron.h"

class Playground
{
public:
  Playground();
  Playground(const Playground& rhs);
  
  void addOutput(int);
  
  vector<*OutputNeuron> olist;

  friend ofstream& operator<<(ofstream& file, Playground p);
};

#endif
