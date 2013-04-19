#include "Signal.h"
#include "Connection.h"
#include "Neuron.h"
#include "Layer.h"
#include "OutputNeuron.h"
#include "InputNeuron.h"
#include "Playground.h"

#include <iostream>
#include <fstream>

using namespace std;

#ifndef __BRAIN__
#define __BRAIN__

//GLOBAL
extern Node ** allNeurons;
extern int neuralNetSize;
extern Connection ** allConnections;
extern int connectionSize;

/*
* The brain contains the three types of Neurons:
*   General Neurons
*   Output Neurons
*   Input Neurons
* It receives the image from the Playground and sends the appropriate signals to the input neurons
* It then analyzes the output of the output neurons and returns an answer to the Playground
*/

class Brain: public Layer
{
private:
  int levelseed; //number of hidden layers
  int middleseed; //size of hidden layers
  Playground* playground;
public:
//CONSTRUCTORS
//	  Brain();
  Brain(Playground*);
  virtual ~Brain();

//MUTATORS
  bool add(InputNeuron * input);

  bool setup();
  bool setup(char* filename);

  char land(char);

//ACCESSORS
  bool save(char* filename) const; //saves the brain to a file
  bool launch(char* signals) const;//takes an array an its size and, for each input neuron, sends the signal to it

  void reset() const;//calls reset on the input nodes, the primary purpose of this to restore normal activation levels

//Brain& mutate() const;//possible future function that would return a mutated version of the current Brain.

//OPERATORS
  bool operator+=(InputNeuron * input){return add(input);}
//Brain& operator+(Brain& rhs);//If ever we wanted to add two brains together
};
#endif
