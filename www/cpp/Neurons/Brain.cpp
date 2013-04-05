#include "Brain.h"
#include "Playground.h"
#include <stdlib.h>
#include "math.h"
//CONSTRUCTORS
Brain::Brain(Playground* play): Layer(0,0)
{
  playground = play;
}

//*****************TO BE IMPLEMENTED*******************
Brain::~Brain()
{
	for(int i=0;i<netSize;i++)
	{
		delete allNeurons[i];
	}
	delete allNeurons;
	for(int i=0;i<connectionSize;i++)
	{
		delete allConnections[i];
	}
	delete allConnections;
}

//MUTATORS

float randWeight(){
  return (rand()%1000)/10000.0f*(rand()%2?1:-1);
}

//setups up an initial brain, randomly
bool Brain::setup()
{
	int inputseed=200;
	middleseed=400;
	int outputseed=10;
	levelseed=2;
	char identifiers[] = {'0','1','2','3','4','5','6','7','8','9'};


	netSize=inputseed + levelseed*middleseed + outputseed;
	length=inputseed;
	int sizeOfOutputs=outputseed;
	connectionSize=inputseed * middleseed + ((int)pow(middleseed,2))*(levelseed-1) + middleseed * outputseed;
        //cout << connectionSize << std::endl;
	allNeurons= new Node*[netSize];

	allConnections = new Connection*[connectionSize];

  	for(int i=0;i<netSize;i++)
  	{
    		allNeurons[i] = new Neuron();
                ((Neuron*)allNeurons[i])->setBias(0);//(rand()%(outputseed*1000))/1000.0f);
//		cout << "BIASES" << ((Neuron*)allNeurons[i])->getBias() << " ";
  	}
	for(int i=0;i<length;i++)
	{
    		allNeurons[i]=new InputNeuron(i);
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
	for(int i=0;i<inputseed;i++)
	{
		for(int j=0;j<middleseed;j++)
		{
			allConnections[(i*middleseed)+j]->setTo(inputseed+j);
			allConnections[(i*middleseed)+j]->setFrom(i);
			allConnections[(i*middleseed)+j]->setWeight(randWeight());
		}
	}
        Layer * prev = this;
	for(int i=0;i<levelseed;i++)
	{
		if(i==levelseed-1)
		{
        	        prev->next = playground;
	                playground -> setBase(netSize-outputseed);
                        playground -> setLength(outputseed);
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<outputseed;k++)
				{
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setTo(netSize-outputseed+k);
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
				        allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setWeight(randWeight());
				}
			}
		}
		else
		{
			Layer * next = new Layer(inputseed + i*middleseed,(i+1)*middleseed);
        	        prev->next = next;
	                prev = next;
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<middleseed;k++)
				{
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setTo((inputseed)+((i+1)*middleseed)+k);
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setWeight(randWeight());
				}
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
  allNeurons = new Node*[netSize];
//  cout << "bias";
  for(int i=0;i<netSize;i++)
  {
    allNeurons[i] = new Neuron();
    float bias = 0;
    file >> bias;
//    cout << " " << bias;
    ((Neuron*)allNeurons[i])->setBias(bias);
  }
  //cout << endl;
  file >> length;
  for(int i=0;i<length;i++)
  {
    int indexOfInput;
    file >> indexOfInput;
    allNeurons[indexOfInput]=new InputNeuron(indexOfInput);
  }
  file >> levelseed;
  file >> middleseed;
  file >> sizeOfOutputs;
  for(int i=0;i<sizeOfOutputs;i++)
  {
    int indexOfOutput;
    char identifierOfOutput;
    file >> indexOfOutput;
    file >> identifierOfOutput;
    playground->addOutput(indexOfOutput, identifierOfOutput);
  }
  playground->setBase(netSize-sizeOfOutputs);
  playground->setLength(sizeOfOutputs);
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
  Layer *prev = this;
  for(int m = 0; m<levelseed;m++)
  {
    prev->next = new Layer(length + (m)*middleseed, middleseed);
    prev = prev->next;
  }
  prev->next = playground;
  playground->next = 0;
  return true;
}

//ACCESSORS
bool Brain::save(char* filename) const
{
  //cout << "saving" << endl;
  ofstream file;
  file.open(filename);
  int i = 0;
  file << netSize << "\n";

  for(int i=0;i<netSize;i++)
  {
    file << ((Neuron*)allNeurons[i])->getBias() << " ";
  }

  file << "\n" << length << "\n";
  for(int i = 0;i<length;i++)
  {
    file << (*((InputNeuron*)allNeurons[i])) << " ";
  }
  #ifndef verbose_output_file
  file << "\n" << levelseed << " " << middleseed;
  #else
  file << "\nlevelseed: " << levelseed << " middleseed: " << middleseed;
  #endif
  //cout << "middle saved" << endl;
  file << "\n";
  file  << (*playground) << "\n";
  //cout << "saved playground" << endl;
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
  Signal * sigs = new Signal[count/3];
  int i = 0;
  for(int m=0;m<count;m++)
  {
    float strength = ((int)signals[m])-48;
    for(int n=0;n<2;n++)
    {
      m++;
      strength+=((int)signals[m])-48;
    }
    sigs[i] = Signal(strength/3);
    i++;
//    cout << "<" << sigs[m].get() << ">";
  }
  for(int m=base;m<base+length;m++)
  {
    allNeurons[m]->receive(sigs[m]);
  }
  return collect();
}

//calls reset on the input nodes, the primary purpose of this to restore normal activation levels
void Brain::reset() const
{
//  for(int m = 0; m < size; m++)
//  {
//    inputs[m]->reset();
//  }
}


//Brain& Brain::mutate() const;//possible future function that would return a mutated version of the current Brain.


char Brain::land(char expected)
{
#ifdef TRAIN
  adjust(expected);
#endif
  char answer = (char)((int)(playground->getOmega(expected)+0.5f)+48);
  return answer;
}

