#include "Node.cpp"
#include "Playground.h"
#include <iostream>
#include <fstream>
using namespace std;

extern int * shm_onlayer;
extern Node ** allNeurons;

Playground::Playground(): Layer(0,0,false)
{
  length=0;
}

void Playground::addOutput(int i, char c)
{
  allNeurons[i] = new OutputNeuron(i, c);
  length++;
}

void Playground::start()
{
  for(int m=base;m<base+length;m++)
  {
    allNeurons[m]->start(index);
  }
}

bool Playground::collect() const
{
  *shm_onlayer = 0;
  cout << "i am trying to collect" << endl;
  return true;
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  file>>c.from;
  file>>c.to;
  file>>c.weight;
  file>>c.previousDelta;
//add to the appropriate neurons, this connection in their array of connections in or out
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
  file<<" previousDelta ";
  file<<c.previousDelta;
  #else
  file<<c.from;
  file<<"\t";
  file<<c.to;
  file<<"\t";
  file<<c.weight;
  file<<"\t";
  file<<c.previousDelta;
  #endif
  return file;
}

ofstream& operator<<(ofstream& file, Playground& p)
{
  #ifdef verbose_output_file
  file << "outputsize";
  #endif
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
//outputs, for each output neuron, the omega which signifies the amount that neuron thinks that it is the right answer.
  for(int i = base; i<base+length;i++)
  {
    float o = ((Neuron*)allNeurons[i])->getOmega();
    cout << "var" << i-base << "=" << (o<0.0001f?0.0f:o) << (i<(base+length-1)?"&":"\n");
  }
  return ((Neuron*)allNeurons[base+((int)expected)-48])->getOmega();
}
