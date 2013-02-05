
#ifndef __CONNECTION__
#define __CONNECTION__

#include "Signal.h"
#include "Neuron.h"
/*
* A Connection represents an edge between two Neurons
* They contain weights
* They are passed Signals, which they then modify by their weight
* And progogate to the next Neuron
* They can be modified by the Playground
*/
class Connection
{
private:
//The weight modifies any signal that is passed through the connection by apply weigh on it and passing weight.
  float weight;
//The neuron that passes to the connection a signal to be transmitted
  Neuron * receiveFrom;
//The neuron that this connection outputs each passed signal to
  Neuron * outputTo;
//the activation of a connection is based on the last signal's strength to pass through this connection
  float activation;

public:
//CONSTRUCTORS
  Connection();
  Connection(const Connection& rhs);
  Connection(float weigh, Neuron * in = NULL, Neuron * out = NULL);
  virtual ~Connection();

//MUTATORS
  void punish(float penalty);
  void reward(float award);

  void setWeight(float newWeight);
  void setIncoming(Neuron * newNeuron);
  void setOutgoing(Neuron * newNeuron);

  void reset();//resets its own activation level, as well as calling reset on the outgoing neuron

  bool send(Signal& S);//returns whether the signal was sent properly 

//ACCESSORS
  bool connectionEstablished() const; //checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.

  float get() const {return getWeight();}
  float getWeight() const;
  
  Neuron* getIncoming() const {return receiveFrom;};
  Neuron* getOutgoing() const {return outputTo;};

  bool wasActivated() const;
//OPERATORS
  bool operator==(const Connection& rhs) const;
  bool operator!=(const Connection& rhs) const;

  Connection& operator=(const Connection& rhs);
};

#endif
