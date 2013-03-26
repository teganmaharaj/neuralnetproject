#include "Brain.h"
#include "Playground.h"
#include <stdlib.h>
#include "math.h"
//CONSTRUCTORS
Brain::Brain(Playground* play)
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
	int inputseed=10;
	int middleseed=100;
	int outputseed=10;
	int levelseed=2;
	char identifiers[] = {'0','1','2','3','4','5','6','7','8','9'};


	netSize=inputseed + levelseed*middleseed + outputseed;
	size=inputseed;
	int sizeOfOutputs=outputseed;
	connectionSize=inputseed * middleseed + ((int)pow(middleseed,levelseed)) + middleseed * outputseed;
        std::cout << connectionSize << std::endl;
	allNeurons= new Node*[netSize];
	inputs = new InputNeuron*[size];

	allConnections = new Connection*[connectionSize];

  	for(int i=0;i<netSize;i++)
  	{
    		allNeurons[i] = new Neuron();
  	}
	for(int i=0;i<size;i++)
	{
	    	delete allNeurons[i];
    		allNeurons[i]=new InputNeuron(i);
    		inputs[i] = (InputNeuron*)allNeurons[i];
	}
	for(int i=netSize-sizeOfOutputs;i<netSize;i++)
	{
    		char identifierOfOutput=identifiers[i-(netSize-sizeOfOutputs)];
    		playground->addOutput(i, identifierOfOutput);
  	}
	for(int i=0;i<connectionSize;i++)
  	{
    		allConnections[i] = new Connection();
  	}
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<middleseed;j++)
		{
			allConnections[(i*middleseed)+j]->setTo(size+j);
			allConnections[(i*middleseed)+j]->setFrom(i);
			allConnections[(i*middleseed)+j]->setWeight((rand()%2)?1:-1);
		}
	}
	for(int i=0;i<levelseed;i++)
	{
		if(i==levelseed-1)
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<outputseed;k++)
				{
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,levelseed))+(j*outputseed)+k]->setTo(netSize-outputseed+k);
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,levelseed))+(j*outputseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
				        allConnections[(inputseed*middleseed)+((int)pow(middleseed,levelseed))+(j*outputseed)+k]->setWeight((rand()%2)?1:-1);
				}
			}

		else
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<middleseed;k++)
				{
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setTo((inputseed)+((i+1)*middleseed)+k);
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setWeight((rand()%2)?1:-1);
				}
			}
	}
	return true;
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
  for(int i=0;i<netSize;i++)
  {
    allNeurons[i] = new Neuron();
  }
  for(int i=0;i<size;i++)
  {
    int indexOfInput;
    file >> indexOfInput;
    delete allNeurons[indexOfInput];
    allNeurons[indexOfInput]=new InputNeuron(indexOfInput);
    inputs[i] = (InputNeuron*)allNeurons[indexOfInput];
  }
  file >> sizeOfOutputs;
  for(int i=0;i<sizeOfOutputs;i++)
  {
    int indexOfOutput;
    char identifierOfOutput;
    file >> indexOfOutput;
    file >> identifierOfOutput;
    playground->addOutput(indexOfOutput, identifierOfOutput);
  }
  file >> connectionSize;
  allConnections = new Connection*[connectionSize];
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
  file << netSize << "\n";
  file << size << "\n";
  for(int i = 0;i<size;i++)
  {
    file << (*(inputs[i])) << " ";
  }
  file << "\n";
  file  << (*playground) << "\n";
  #ifdef verbose_output_file
  file << "connectionsize ";
  #endif
  file << connectionSize << "\n";
  for(int i = 0;i < connectionSize; i++)
  {
    file << (*(allConnections[i])) << "\n";
  }
  file.close();
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
    sigs[m] = Signal(((int)signals[m])-48);
    cout << "<" << sigs[m].get() << ">";
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


