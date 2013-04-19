
#ifndef __CONNECTION__
#define __CONNECTION__

#include "Signal.h"
#include "Node.cpp"
#include <fstream>

using namespace std;
/*
* A Connection represents an edge between two Nodes
* They contain weights
* They are passed Signals, which they then modify by their weight
* And progogate to the next Node
* They can be modified by the Playground
*/

extern Node ** allNeurons;
extern float eta;

const float alpha = 0.4f;

class Connection
{
private:
//The weight modifies any signal that is passed through the connection by apply weigh on it and passing weight.
  float weight;
//The neuron that passes to the connection a signal to be transmitted
  int from;
//The neuron that this connection outputs each passed signal to
  int to;
//the activation of a connection is based on the last signal's strength to pass through this connection
  float activation;
//for use with the momentuum
  float previousDelta;

public:
//CONSTRUCTORS
  Connection();
  Connection(const Connection& rhs);
  virtual ~Connection();

//MUTATORS
//adjusts this connection's weight
  void adjust(char);

  void setWeight(float newWeight);
  void setTo(int index);
  void setFrom(int index);

  void reset();//resets its own activation level, as well as calling reset on the outgoing neuron

  bool send(Signal& S);//returns whether the signal was sent properly 

//ACCESSORS
  bool connectionEstablished() const; //checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.

  float get() const {return getWeight();}
  float getWeight() const;
  
  int getFrom() const {return from;};
  int getTo() const {return to;};

  bool wasActivated() const  ;
  float getActivation() const;
//OPERATORS
  Connection& operator=(const Connection& rhs);
  
  friend ifstream& operator>>(ifstream&,Connection&);
  friend ofstream& operator<<(ofstream&,Connection&);
};

#endif
