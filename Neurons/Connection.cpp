#include "Connection.h"
//CONSTRUCTORS
Connection::Connection()
{
  weight = 0.f;
  activation = 0.f;
  receiveFrom = NULL;
  outputTo = NULL;
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

void Connection::reset()//resets its own activation level, as well as calling reset on the outgoing neuron
{
  activation = 0.f;
  outputTo -> reset();
}

bool Connection::send(Signal& S) //returns whether the connection was propogated successfully
{
  S.weigh(weight);
  activation = S.get();
  if(!connectionEstablished())
    return false;
  //else
  return outputTo -> receive(S);
}


//ACCESSORS
bool Connection::connectionEstablished() const //checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.
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
