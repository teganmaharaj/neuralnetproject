#ifndef __NODE__
#define __NODE__

#include "Signal.h"

/*
* Neurons are the main data type of the neural net
* They must receive and send signals from other neurals
* They must activate when excited, based on a function (tranh for example)
* They must they must modify their outgoing weights based on input by the Playground
* They can delete connections that drop below a threshold(become close to 0)
*/

using namespace std;

class Node
{
private:
public:
  virtual bool receive();
  virtual bool send(Signal&);
  virtual void reset();

};


#endif