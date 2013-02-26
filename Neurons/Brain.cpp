#include "Brain.h"
#include "Signal.h"
#include "Connection.h"
#include "InputNeuron.h"
#include "OutputNeuron.h"
#include "Neuron.h"
#include <iostream>
#include <fstream>

using namespace std;

//CONSTRUCTORS
Brain::Brain()
{
}
Brain::Brain(Playground& play)
{
  playground = play;
}
Brain::~Brain()
{
}

//MUTATORS
bool Brain::add(InputNeuron * input)
{
}

//setups up an initial brain, randomly
bool Brain::setup()
{
}
bool Brain::setup(char* filename)
{
  int sizeOfOutputs;
  ifstream file;
  file.open(filename);
  file >> netSize;
  file >> size;
  inputs = new InputNeuron*[size];
  allNeurons = new Neuron*[netSize];
  allConnections = new Connection*[connectionSize];
  for(int i=0;i<allNeurons;i++)
  {
    allNeurons[i] = new Neuron();
  }
  for(int i=0;i<size;i++)
  {
    int indexOfInput;
    file >> indexOfInput;
    inputs[i] = new InputNeuron(*(allNeurons[indexOfInput]));
  }
  file >> sizeOfOutputs;
  for(int i=0;i<sizeOfOutputs;i++)
  {
    int indexOfOutput;
    file >> indexOfOutput;
    playground.addOutput(indexOfOutput);
  }
  file >> connectionSize;
  for(int i=0;i<connectionSize;i++)
  {
    allConnections[i] = new Connection();
  }
  for(int i=0;!file.eof() && i < connectionSize; i++)
  {
    file >> (*(allConnection[i]));
  }
  file.close();
  return true;
}

//ACCESSORS
bool Brain::save(char* filename) const
{
  ofstream file;
  file.open(filename);
  int i = 0;
  file << netSize;
  file << size;
  for(int i = 0;i<size;i++)
  {
    file << (*(inputs[i]));
  }
  file << playground;
  file << connectionSize;
  for(int i = 0;i < connectionSize; i++)
  {
    file << (*(allConnections[i]));
  }
  return true;
}

//loads the signal from the data files from the ../data folder(as specified). After loading it launches
bool Brain::load(char* filename) const
{
  int x;
  int y;
  ifstream file;
  file.open(filename);
  file >> x;
  file >> y;
  Signal * sigs = new Signal[x*y];
  for(int m=0;m<x;m++)
  {
    for(int n=0;n<y;n++)
    {
      file >> sigs[m*x+n];
    }
  }
  return launch(sigs, x*y);
}

//takes an array an its size and, for each input neuron, sends the signal to it
bool Brain::launch(Signal * input, int s_size) const
{
  bool doom = false;
  for(int m=0;m < size && m < s_size;m++)
  {
    doom = doom && inputs[m]->receive(input[m]);
  }
  return doom;
}

//calls reset on the input nodes, the primary purpose of this to restore normal activation levels
void Brain::reset() const
{
  for(int m = 0; m < size; m++)
  {
    inputs[m]->reset();
  }
}

//Brain& Brain::mutate() const;//possible future function that would return a mutated version of the current Brain.


