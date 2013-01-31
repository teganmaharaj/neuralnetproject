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
  ifstream file;
  file.open(filename);
  int i = 0;
  file >> netSize;
  file >> size;
  inputs = new InputNeuron*[size];
  allNeurons = new Neuron*[netSize];
  Neuron temp;
  while(!file.eof() && i < size)
  {
    file >> temp;
    inputs[i] = new InputNeuron(temp);
    i++;
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
  while(i < size)
  {
    file << (*(inputs[i]));
    i++;
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

bool Brain::launch(Signal * input, int s_size) const//takes an array an its size and, for each input neuron, sends the signal to it
{
  bool doom;
  for(int m=0;m < size && m < s_size;m++)
  {
    doom = doom && inputs[m]->receive(input[m]);
  }
  return doom;
}

bool Brain::receive(OutputNeuron * fired) const//when an output Neuron fires, it is caught here
{
  cout << fired->getIdentifier() << endl;
}

bool Brain::disipline(float amount) const
{
  for(int m=0;m < connections.size() ; m++)
  {
    if(connections[m].wasActivated())
      connections[m].punish(amount);
  }
  return true;
}

bool Brain::reward(float amount) const
{
  for(int m=0;m < connections.size() ; m++)
  {
    if(connections[m].wasActivated())
      connections[m].reward(amount);
  }
  return true;
}

void Brain::reset() const//calls reset on the input nodes, the primary purpose of this to restore normal activation levels
{
  for(int m = 0; m < size; m++)
  {
    inputs[m]->reset();
  }
}

//Brain& Brain::mutate() const;//possible future function that would return a mutated version of the current Brain.


