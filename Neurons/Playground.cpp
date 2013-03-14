#include "Playground.h"

#include <fstream>
using namespace std;

Playground::Playground()
{
}
Playground::Playground(const Playground& rhs)
{
}

void Playground::addOutput(int i)
{
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  return file;
}

ofstream& operator<<(ofstream& file, Connection& c)
{
  return file;
}

ofstream& operator<<(ofstream& file, Playground p)
{
  return file;
}

#include "InputNeuron.h"
ofstream& operator<<(ofstream& file, InputNeuron& rhs)
{
  return file;
}