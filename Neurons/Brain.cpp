#include "Brain.h"

//CONSTRUCTORS
Brain::Brain()
{
}
Brain::Brain(Playground& play)
{
  playground = play;
}

//*****************TO BE IMPLEMENTED*******************
Brain::~Brain()
{
}

//MUTATORS

//*****************TO BE IMPLEMENTED*******************
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
  allNeurons = new Node*[netSize];
  allConnections = new Connection*[connectionSize];
  for(int i=0;i<netSize;i++)
  {
    allNeurons[i] = new Neuron();
  }
  for(int i=0;i<size;i++)
  {
    int indexOfInput;
    file >> indexOfInput;
    delete allNeurons[i];
    allNeurons[i]=new InputNeuron(indexOfInput);
    inputs[i] = (InputNeuron*)allNeurons[i];
  }
  file >> sizeOfOutputs;
  for(int i=0;i<sizeOfOutputs;i++)
  {
    int indexOfOutput;
    char identifierOfOutput;
    file >> indexOfOutput;
    file >> identifierOfOutput;
    playground.addOutput(indexOfOutput, identifierOfOutput);
  }
  file >> connectionSize;
  for(int i=0;i<connectionSize;i++)
  {
    allConnections[i] = new Connection();
  }
  for(int i=0;!file.eof() && i < connectionSize; i++)
  {
    file >> (*(allConnections[i]));
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
bool Brain::launch(char* signals) const
{
  int count = 0;
  char* ptr = signals;
  while(*ptr++)
    count++;
  Signal * sigs = new Signal[count];
  for(int m=0;m<count;m++)
  {
    sigs[m] = new Signal(((int)signals[m])-48);
  }
  bool doom = true;
  for(int m=0;m < size && m < count;m++)
  {
    doom = doom && inputs[m]->receive(sigs[m]);
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


