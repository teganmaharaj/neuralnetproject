#include "Signal.h"
#include "Connection.h"
#include "Neuron.h"
#include "OutputNeuron.h"
#include "InputNeuron.h"
#include "Playground.h"

#include <iostream>
#include <fstream>

using namespace std;

#ifndef __BRAIN__
#define __BRAIN__

//GLOBAL

Node ** allNeurons;
int netSize;
Connection ** allConnections;
int connectionSize;

/*
* The brain contains the three types of Neurons:
*   General Neurons
*   Output Neurons
*   Input Neurons
* It receives the image from the Playground and sends the appropriate signals to the input neurons
* It then analyzes the output of the output neurons and returns an answer to the Playground
*/
class Brain
{
private:
  InputNeuron ** inputs;
  int size;

  Playground playground;
public:
//CONSTRUCTORS
  Brain();
  Brain(Playground&);
  virtual ~Brain();

//MUTATORS
  bool add(InputNeuron * input);

  bool setup();
  bool setup(char* filename);

//ACCESSORS
  bool save(char* filename) const;
  bool load(char* filename) const;//loads data files from the ../data folder(as specified). After loading it launches
  bool launch(Signal * input, int size) const;//takes an array an its size and, for each input neuron, sends the signal to it

  void reset() const;//calls reset on the input nodes, the primary purpose of this to restore normal activation levels

//Brain& mutate() const;//possible future function that would return a mutated version of the current Brain.

//OPERATORS
  bool operator+=(InputNeuron * input){return add(input);}
//Brain& operator+(Brain& rhs);//If ever we wanted to add two brains together
};
#endif
