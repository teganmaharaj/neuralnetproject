#ifndef __NEURON__
#define __NEURON__

#include "Signal.h"
#include "Node.cpp"
#include "Connection.h"
#include <vector>
#include <fstream>

/*
* Neurons are the main data type of the neural net
* They must receive and send signals from other neurals
* They must activate when excited, based on a function (tranh for example)
* They must they must modify their outgoing weights based on input by the Playground
* They can delete connections that drop below a threshold(become close to 0)
*/

using namespace std;

extern float eta;

class Neuron: public Node
{
public:
//instance variables
  vector <Connection*> connectionsIn;
  vector <Connection*> connectionsOut;
protected:
  float accumulated;//sum
public:
  float omega;//answer
  float delta;//error in answer
  float bias;//this neuron's bias
public:
//constructors/destructors
  Neuron();
  ~Neuron(){}

//receive pools all the signals sent to this neuron
  bool receive(Signal&);
//send propogates the signal forward
  bool send(Signal&) const;
//reset basically does nothing at this point
  void reset();
//adjust reconfigures the bias for this neuron and the connectionsIn for this neuron
  void adjust(char);
//collect is the method that analyzes the accumulated signal, and calls send to propogate it forward
  bool collect() const;

  void start(int);

//GETTERS AND SETTERS
  float getAccumulated() const{return accumulated;};
  void setBias(float b){bias = b;};
  float getBias(){return bias;};

//these are actual functions that only appears as getters
  float getOmega();
  float getDelta(char);

//the >> global operator can act as if it is a method of Connections
  friend ifstream& operator>>(ifstream&, Connection&);

};

#endif
