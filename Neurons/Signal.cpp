#include "Signal.h"

//CONSTRUCTORS

Signal::Signal()
{
}

Signal::Signal(const Signal&rhs)
{
}

Signal::Signal(float str)
{
}

Signal::~Signal()
{
}

//MUTATORS

void Signal::weigh(float weight)
{
}

//ACCESSORS

float Signal::get() const
{
  return strength;
}

//OPERATORS
bool Signal::operator==(const Signal& rhs) const
{
  return false;
}
bool Signal::operator!=(const Signal& rhs) const
{
  return false;
}

bool Signal::operator> (const Signal& rhs) const
{
  return false;
}
bool Signal::operator>=(const Signal& rhs) const
{
  return false;
}
bool Signal::operator< (const Signal& rhs) const
{
  return false;
}
bool Signal::operator<=(const Signal& rhs) const
{
  return false;
}

bool Signal::operator> (float str) const
{
  return false;
}
bool Signal::operator>=(float str) const
{
  return false;
}
bool Signal::operator< (float str) const
{
  return false;
}
bool Signal::operator<=(float str) const
{
  return false;
}

Signal& Signal::operator=(const Signal& rhs)
{
  return (*this);
}
Signal& Signal::operator=(float str)
{
  return (*this);
}
