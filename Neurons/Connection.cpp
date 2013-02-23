#include "Connection.h"
//CONSTRUCTORS
Connection::Connection()
{
  weight = 0.0f;
  activation = 0.0f;
  receiveFrom = 0;
  outputTo = 0;
}
Connection::Connection(const Connection& rhs)
{
  weight = rhs.weight;
  receiveFrom = rhs.receiveFrom;
  outputTo   = rhs.outputTo;
  activation = rhs.activation;
}
Connection::Connection(float weigh, Neuron * incoming, Neuron * outgoing)
{
  weight = weigh;
  receiveFrom = incoming;
  outputTo = outgoing;
  activation = 0.f;
}

Connection::~Connection()
{
}

//MUTATORS
void Connection::punish(float penalty)
{
  weight *= penalty;
}
void Connection::reward(float award)
{
  weight *= award;
}

void Connection::setWeight(float newWeight)
{
  weight = newWeight;
}
void Connection::setIncoming(Neuron * newNeuron)
{
  receiveFrom = newNeuron;
}
void Connection::setOutgoing(Neuron * newNeuron)
{
  outputTo = newNeuron;
}

//resets its own activation level, as well as calling reset on the outgoing neuron
void Connection::reset()
{
  activation = 0.f;
  outputTo -> reset();
}

//returns whether the connection was propogated successfully
bool Connection::send(Signal& S) 
{
  S.weigh(weight);
  activation = S.get();
  if(!connectionEstablished())
    return false;
  //else
  return outputTo -> receive(S);
}


//ACCESSORS
//checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.
bool Connection::connectionEstablished() const 
{
  return receiveFrom != NULL && outputTo != NULL;
}

float Connection::getWeight() const
{
  return weight;
}

bool Connection::wasActivated() const
{
  return activation > 0.1f || activation < -0.1f;
}

float Connection::getActivation() const
{
  return activation;
}

//OPERATORS
bool Connection::operator==(const Connection& rhs) const
{
  return outputTo == rhs.outputTo && receiveFrom == rhs.receiveFrom && weight == rhs.weight;
}
bool Connection::operator!=(const Connection& rhs) const
{
  return outputTo != rhs.outputTo && receiveFrom != rhs.receiveFrom && weight != rhs.weight;
}

Connection& Connection::operator=(const Connection& rhs)
{
  weight = rhs.weight;
  receiveFrom = rhs.receiveFrom;
  outputTo = rhs.outputTo;
  activation = rhs.activation;
  return (*this);
}
