#include "Signal.h"
#include "Connection.h"
#include "Neuron.h"
#include "OutputNeuron.h"
#include "InputNeuron.h"
#ifndef __BRAIN__
#define __BRAIN__

//GLOBAL
Neuron ** allNeurons;
int netSize;

/*
* The brain contains the three types of Neurons:
* General Neurons
* Output Neurons
* Input Neurons
* It receives the image from the Playground and sends the appropate signals to the input neurons
* It then analyzes the output of the output neurons and returns an answer to the Playground
*/
class Brain
{
private:
  InputNeuron ** inputs;
  int size;
public:
//CONSTRUCTORS
  Brain();
  virtual ~Brain();

//MUTATORS
  bool add(InputNeuron * input);

  bool setup();
  bool setup(char* filename);

//ACCESSORS
  bool save(char* filename) const;
  bool load(char* filename) const;//loads data files from the ../data folder(as specified). After loading it launches
  bool launch(Signal * input, int size) const;//takes an array an its size and, for each input neuron, sends the signal to it

  bool receive(OutputNeuron * fired) const;//when an output Neuron fires, it is caught here
  bool disipline(float penalty) const;//by the passed penalty, this method punishes all activated connections
  bool reward(float award) const;//by the passed award, this method rewards all activated connections

  void reset() const;//calls reset on the input nodes, the primary purpose of this to restore normal activation levels

//Brain& mutate() const;//possible future function that would return a mutated version of the current Brain.

//OPERATORS
  bool operator+=(InputNeuron * input){return add(input);}
//Brain& operator+(Brain& rhs);//If ever we wanted to add two brains together
};
#endif
