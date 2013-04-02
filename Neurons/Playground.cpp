#include "Playground.h"
#include <iostream>
#include <fstream>
using namespace std;

Playground::Playground(): Layer(0,0)
{
}

void Playground::addOutput(int i, char c)
{
  allNeurons[i] = new OutputNeuron(i, c);
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  file>>c.from;
  file>>c.to;
  file>>c.weight;
  ((Neuron*)(allNeurons[c.from]))->connectionsOut.push_back(&c);
  ((Neuron*)(allNeurons[c.to]))  ->connectionsIn.push_back(&c);
  return file;
}

ofstream& operator<<(ofstream& file, Connection& c)
{
  #ifdef verbose_output_file
  file<<"From ";
  file<<c.from;
  file<<" to ";
  file<<c.to;
  file<<" : "; 
  file<<c.weight;
  #else
  file<<c.from;
  file<<"\t";
  file<<c.to;
  file<<"\t";
  file<<c.weight;
  #endif
  return file;
}

ofstream& operator<<(ofstream& file, Playground& p)
{
  #ifdef verbose_output_file
  file << "outputsize";
  #endif
  cout << "p.length = " << p.length << endl;
  file << p.length;
  #ifdef verbose_output_file
  file << " above";
  #endif
  file << "\n";
  for(int i=p.base;i<p.base+p.length;i++)
  {
    #ifdef verbose_output_file
    file << "index ";
    #endif
    file << ((OutputNeuron*)allNeurons[i])->getIndex();
    file << " ";
    #ifdef verbose_output_file
    file << "id ";
    #endif
    file << ((OutputNeuron*)allNeurons[i])->getIdentifier();
    file << "\n";
  }
  return file;
}

#include "InputNeuron.h"
ofstream& operator<<(ofstream& file, InputNeuron& rhs)
{
  file << rhs.index;
  return file;
}

float Playground::getOmega(char expected)
{
  return ((Neuron*)allNeurons[base+((int)expected)-48])->getOmega();
}
