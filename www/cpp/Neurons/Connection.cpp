#include "Connection.h"
#include <iostream>
using namespace std;
//CONSTRUCTORS
Connection::Connection()
{
  weight     = 0.0f;
  activation = 0.0f;
  from       = 0;
  to         = 0;
  previousDelta  = 0.0f;
}
Connection::Connection(const Connection& rhs)
{
  weight     = rhs.weight;
  from       = rhs.from;
  to         = rhs.to;
  activation = rhs.activation;
}

Connection::~Connection()
{
}

//MUTATORS
//adjusts this connection's weight
void Connection::adjust(char expected)
{
//based on the omega from and the omega to and the momentum
  previousDelta = - eta * allNeurons[to]->getDelta(expected) * allNeurons[from]->getOmega() + alpha * previousDelta;
  weight += previousDelta;
}

void Connection::setWeight(float newWeight)
{
  weight = newWeight;
}
void Connection::setFrom(int index)
{
  from = index;
}
void Connection::setTo(int index)
{
  to = index;
}

//resets its own activation level, as well as calling reset on the outgoing neuron
void Connection::reset()
{
  activation = 0.f;
  allNeurons[to] -> reset();
}

//returns whether the connection was propagated successfully
bool Connection::send(Signal& S) 
{
//weigh the signal down by this connection's weight
  S.weigh(weight);
  activation = S.get();
  if(!connectionEstablished())
    return false;
  return allNeurons[to] -> receive(S);
}


//ACCESSORS

//checks if there is an incoming and outgoing neuron, i.e., if a signal can be passed.
bool Connection::connectionEstablished() const 
{
  return allNeurons[from] && allNeurons[to];
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
Connection& Connection::operator=(const Connection& rhs)
{
  weight = rhs.weight;
  from = rhs.from;
  to = rhs.to;
  activation = rhs.activation;
  return (*this);
}
