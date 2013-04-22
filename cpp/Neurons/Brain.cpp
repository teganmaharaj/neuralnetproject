#include "Brain.h"
#include "Playground.h"
#include <stdlib.h>
#include "math.h"
//CONSTRUCTORS
Brain::Brain(Playground* play): Layer(0,0)
{
  playground = play;
}
//DESTRUCTOR
Brain::~Brain()
{

	for(int i=0;i<neuralNetSize;i++)
	{
		delete allNeurons[i];//deletes all neurons
	}
	delete allNeurons;
	for(int i=0;i<connectionSize;i++)
	{
		delete allConnections[i];// deletes all connections
	}
	delete allConnections;
}

//MUTATORS

float randWeight(){
  //gets a random number between 0.1 and -0.1
  return (rand()%1000)/10000.0f*(rand()%2?1:-1);
}

//setups up an initial brain, randomly
bool Brain::setup()
{
	//the number of input neurons is 200
	int inputseed=200;
	//number of neurons per hidden layer is 400
	middleseed=400;
	//number of outputs is 10(one for each number)
	int outputseed=10;
	//number of hidden layers is 2
	levelseed=2;
	//what each output neuron represents
	char identifiers[] = {'0','1','2','3','4','5','6','7','8','9'};

	//the "neuralNetSize" which is the number of neurons in the neural net, is equals to all the inputs, plus all the hidden layer plus all the outputs
	neuralNetSize=inputseed + levelseed*middleseed + outputseed;
	//lenth is a variable held by layer, for the brain it is the inputseed because the length is the number of neurons in your layer
	length=inputseed;
	//sizeOfOutputs was used in the original setup function, so it is a legacy name for the output seed
	int sizeOfOutputs=outputseed;
	//the number of connections between a given layer and the next is the that layers number of neurons multiplied by the number of neurons in the next layer
	//to find the connectionSize, we add up each layer's connections
	connectionSize=inputseed * middleseed + ((int)pow(middleseed,2))*(levelseed-1) + middleseed * outputseed;
	//initialize the neural net array, which has size: neuralNetSize
	allNeurons= new Node*[neuralNetSize];
	//initialize the connection array, with the size of connectionSize
	allConnections = new Connection*[connectionSize];

  	for(int i=0;i<neuralNetSize;i++)
  	{
    		allNeurons[i] = new Neuron();//create a node for each element in the neural net array
                ((Neuron*)allNeurons[i])->setBias(0);//all biases start at 0
  	}
	for(int i=0;i<length;i++)
	{
    		allNeurons[i]=new InputNeuron(i);//for each input neuron, replace the neuron at that index by an actual input neuron
	}
	for(int i=neuralNetSize-sizeOfOutputs;i<neuralNetSize;i++)
	{
    		char identifierOfOutput=identifiers[i-(neuralNetSize-sizeOfOutputs)];
    		playground->addOutput(i, identifierOfOutput); //for each output neuron, replace the neuron at that index by an actual output neuron
  	}
	for(int i=0;i<connectionSize;i++)
  	{
    		allConnections[i] = new Connection();//create a connection for all the connecitons in the connections array
  	}
	for(int i=0;i<inputseed;i++)
	{
		for(int j=0;j<middleseed;j++)
		{
			allConnections[(i*middleseed)+j]->setTo(inputseed+j);//set which index of the forward neuron with respect to this connection
			allConnections[(i*middleseed)+j]->setFrom(i);        //set which index of the backward neuron with respect to this conection
			allConnections[(i*middleseed)+j]->setWeight(randWeight()); //give it a random weight between 0.1 and -0.1
		}
	}
        Layer * prev = this;
	for(int i=0;i<levelseed;i++)
	{
		if(i==levelseed-1)
		{
			//this is the last layer, so connect things to the playground and the output neurons
        	        prev->next = playground;
	                playground -> setBase(neuralNetSize-outputseed);//sets the "base" or the first element of the layer
                        playground -> setLength(outputseed);//sets the size of playground(last) layer to the size of the output neurons
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<outputseed;k++)
				{
					//connects the last hidden layer to the output neuron layer
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setTo(neuralNetSize-outputseed+k);
					allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
					//gives them a random weight between 0.1 and -0.1
				        allConnections[(inputseed*middleseed)+((int)pow(middleseed,2))*(levelseed-1)+(j*outputseed)+k]->setWeight(randWeight());
				}
			}
		}
		else
		{
			//here we are in the middle of the neural net, so connect the previous layer to this layer
			//first create this layer
			Layer * next = new Layer(inputseed + i*middleseed,(i+1)*middleseed);
			//then connect the previous to this layer
        	        prev->next = next;
			//then set the next as the current previous, so that the next time, this layer will be linked to its next
	                prev = next;
			for(int j=0;j<middleseed;j++)
			{
				for(int k=0;k<middleseed;k++)
				{
					//connect all the neurons from this layer to the previous layer's neurons
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setTo((inputseed)+((i+1)*middleseed)+k);
					allConnections[(inputseed*middleseed)+(i*middleseed)+(j*middleseed)+k]->setFrom((inputseed)+(i*middleseed)+j);
					//give them random weights
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
  //first in the brain file is the neural net's size
  file >> neuralNetSize;
  //make the array of neurons
  allNeurons = new Node*[neuralNetSize];
  for(int i=0;i<neuralNetSize;i++)
  {
    //fill that array with generic neurons
    allNeurons[i] = new Neuron();
    float bias = 0;
    //retrieve and set the bias for each of the neurons just created
    file >> bias;
    ((Neuron*)allNeurons[i])->setBias(bias);
  }
  //get the input neuron size
  file >> length;
  for(int i=0;i<length;i++)
  {
    int indexOfInput;
    //get all the indices that are input neurons, and make actual InputNeurons out of them(replacing the old generic neuron that was there before)
    file >> indexOfInput;
    allNeurons[indexOfInput]=new InputNeuron(indexOfInput);
  }
  //get the number of hidden layers there are
  file >> levelseed;
  //get the number of hidden neurons per layer
  file >> middleseed;
  //get the number of outputs
  file >> sizeOfOutputs;
  for(int i=0;i<sizeOfOutputs;i++)
  {
    int indexOfOutput;
    char identifierOfOutput;
    //for each output neuron retrieve and set the index, as well as the identifier(which is the character which that output neuron is suppose to be affiliated with)
    file >> indexOfOutput;
    file >> identifierOfOutput;
    playground->addOutput(indexOfOutput, identifierOfOutput);
  }
  //set the base and length of the playground
  playground->setBase(neuralNetSize-sizeOfOutputs);
  playground->setLength(sizeOfOutputs);
  //get the number of connections
  file >> connectionSize;
  allConnections = new Connection*[connectionSize];
  for(int i=0;i<connectionSize;i++)
  {
    allConnections[i] = new Connection();//fill the connections array
  }
  for(int i=0;!file.eof() && i < connectionSize; i++)
  {
    file >> (*(allConnections[i]));//read from the file, each connection(from to weight previousDelta)
  }
  file.close();
  //setup the layer to layer associations
  //starting with the brain
  Layer *prev = this;
  for(int m = 0; m<levelseed;m++)
  {
    //go through each of the hidden layers and make a new one based on the middle seed
    prev->next = new Layer(length + (m)*middleseed, middleseed);
    prev = prev->next;
  }
  //the last layer of the hidden layers' next is set to the playground(the output neurons)
  prev->next = playground;
  playground->next = 0; //initialize the playground's next to zero
  return true;
}

//ACCESSORS
bool Brain::save(char* filename) const
{
  ofstream file;
  file.open(filename);
  int i = 0;
  //file format first has the neural net's size
  file << neuralNetSize << "\n";

  for(int i=0;i<neuralNetSize;i++)
  {
    //then all the biases
    file << ((Neuron*)allNeurons[i])->getBias() << " ";
  }

  //then the number of input neurons
  file << "\n" << length << "\n";
  for(int i = 0;i<length;i++)
  {
    //then the indexes for each input neuron
    file << (*((InputNeuron*)allNeurons[i])) << " ";
  }
  #ifndef verbose_output_file
  // then the number of hidden neuron layers and the number of neurons for each of those layers
  file << "\n" << levelseed << " " << middleseed;
  #else
  file << "\nlevelseed: " << levelseed << " middleseed: " << middleseed;
  #endif
  file << "\n";
  //then all the output neuron's information
  file  << (*playground) << "\n";
  #ifdef verbose_output_file
  file << "connectionsize ";
  #endif
  //then the size of the connections
  file << connectionSize << "\n";
  for(int i = 0;i < connectionSize; i++)
  {
    //then the information for each connection
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
  //first we find out how many signals we have
  while(*ptr++)
    count++;
  //then we make an array for a third of the array
  Signal * sigs = new Signal[count/3];
  int i = 0;
  for(int m=0;m<count;m++)
  {
    //the signal at m will be a char, either 1 or 0, which tells the brain which inputs are firing or not
    float strength = ((int)signals[m])-48;
    for(int n=0;n<2;n++)
    {
      m++;
      strength+=((int)signals[m])-48;
    }
    //average every three inputs into a single signal
    sigs[i] = Signal(strength/3);
    i++;
  }
  for(int m=base;m<base+length;m++)
  {
    //for each input neuron, give it a initial signal
    allNeurons[m]->receive(sigs[m]);
  }
  //call the layer method "collect"
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
  //if you are training the neural net, call adjust on this layer which will propgate the signal forward
  adjust(expected);
#endif
  //otherwise just return the answer you think it is
  char answer = (char)((int)(playground->getOmega(expected)+0.5f)+48);
  return answer;
}

