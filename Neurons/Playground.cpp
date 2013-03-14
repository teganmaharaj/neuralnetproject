#include "Playground.h"

#include <fstream>
using namespace std;

Playground::Playground()
{
  olist=vector<OutputNeuron*>();
}
Playground::Playground(const Playground& rhs)
{
  for(int i=0;i<rhs.olist.size();i++)
  {
    olist.push_back(rhs.olist[i]);
  }
}

void Playground::addOutput(int i, char c)
{
  allNeurons[i] = new OutputNeuron(*(allNeurons[i]),i, c);
  olist.push_back((OutputNeuron*)allNeurons[i]);
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  file>>c.weight;
  file>>c.idFrom;
  file>>c.idTo;
  return file;
}

ofstream& operator<<(ofstream& file, Connection& c)
{
  file<<c.weight;
  file<<c.idFrom;
  file<<c.idTo;
  return file;
}

ofstream& operator<<(ofstream& file, Playground p)
{
  for(int i=0;i<p.olist.size();i++)
  {
    file<<p.olist[i]->getIndex();
    file<<p.olist[i]->getIdentifier();
  }
  return file;
}

#include "InputNeuron.h"
ofstream& operator<<(ofstream& file, InputNeuron& rhs)
{
  file<<rhs.index;
  return file;
}

//*****************TO BE IMPLEMENTED*******************
bool Playground :: receive()
{
  return false;
}  

