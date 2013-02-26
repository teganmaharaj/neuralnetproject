#include "Signal.h"

//CONSTRUCTORS

Signal::Signal()
{
  strength = 0.f;
}

Signal::Signal(const Signal&rhs)
{
  strength = rhs.strength;
}

Signal::Signal(float str)
{
  strength = str;
}

Signal::~Signal()
{
}

//MUTATORS

void Signal::weigh(float weight)
{
  strength *= weight;
}

//ACCESSORS

float Signal::get() const
{
  return strength;
}

//OPERATORS
bool Signal::operator==(const Signal& rhs) const
{
  return strength == rhs.strength;
}
bool Signal::operator!=(const Signal& rhs) const
{
  return strength != rhs.strength;;
}

bool Signal::operator> (const Signal& rhs) const
{
  return strength > rhs.strength;
}
bool Signal::operator>=(const Signal& rhs) const
{
  return strength >= rhs.strength;
}
bool Signal::operator< (const Signal& rhs) const
{
  return strength < rhs.strength;
}
bool Signal::operator<=(const Signal& rhs) const
{
  return strength <= rhs.strength;
}

bool Signal::operator> (float str) const
{
  return strength > str;
}
bool Signal::operator>=(float str) const
{
  return strength >= str;
}
bool Signal::operator< (float str) const
{
  return strength < str;
}
bool Signal::operator<=(float str) const
{
  return strength <= str;
}

Signal& Signal::operator=(const Signal& rhs)
{
  strength = rhs.strength;
  return (*this);
}
Signal& Signal::operator=(float str)
{
  strength = str;
  return (*this);
}

ifstream& operator>>(ifstream& file, Signal& rhs)
{
  file >> rhs.strength;
  return  file;
}

