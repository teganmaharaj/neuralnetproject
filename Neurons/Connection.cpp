#include "Connection.h"
//CONSTRUCTORS
Connection::Connection()
{
}
Connection::Connection(const Connection& rhs)
{
}
Connection::Connection(float weight, Neuron * incoming, Neuron * outgoing)
{
}

//MUTATORS
void Connection::punish(float penalty)
{
}
void Connection::reward(float award)
{
}

void Connection::setWeight(float newWeight)
{
}
void Connection::setIncoming(Neuron * newNeuron)
{
}
void Connection::setOutgoing(Neuron * newNeuron)
{
}

void Connection::reset()//resets its own activation level, as well as calling reset on the outgoing neuron
{
}

//ACCESSORS
bool Connection::connectionEstablished() const //checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.
{
  return false;
}

bool Connection::send(Signal& S) const//returns whether the connection was properly sent
{
  return false;
}

float Connection::getWeight() const
{
  return weight;
}

//OPERATORS
bool Connection::operator==(const Connection& rhs) const
{
  return false;
}
bool Connection::operator!=(const Connection& rhs) const
{
  return false;
}

Connection& Connection::operator=(const Connection& rhs)
{
  return (*this);
}
