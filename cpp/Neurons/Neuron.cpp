#include "Neuron.h"
#include "math.h"
#include <iostream>
#include <stdlib.h>
#include "System.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHM_RUNNING_SZ     1
#define SHM_ONLAYER_SZ     4
#define SHM_COLLECTED_SZ   4

extern int shmid_running;
extern int shmid_onlayer;
extern int shmid_collected;
extern key_t key_running;
extern key_t key_onlayer;
extern key_t key_collected;
extern char * shm_running;
extern int  * shm_onlayer;
extern int  * shm_collected;

//extern System sys;
//extern bool System::isRunning;
//extern key_t shmid;

Neuron::Neuron(): Node()
{
  accumulated    = 0.0f;
  bias           = 0.0f;
  delta	         = 0.0f;
  omega          = 0.0f;
  connectionsIn  = vector <Connection*>();
  connectionsOut = vector <Connection*>();
}
//Global functions for determining how much of the signal is propogated
float sig(float x)
{
  return 1/(1+exp(-x));
}
float diffsig(float x)
{
  return -(sig(x)*sig(x)-sig(x));
}

bool Neuron::receive(Signal& signal)
{
  //just add the signal to accumulated
  accumulated += signal.get();
  return true;
}
bool Neuron::collect() const
{
  //modify the sum of signals plus a bias based on the sig function
  float strength = sig(accumulated+bias);
  //make a new signal out of it
  Signal sendSignal = Signal(strength);
  //send it to all of this neurons outConnections
  send(sendSignal);
  return true;
}

bool Neuron::send(Signal& outgoing) const
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		Signal s = Signal(outgoing);
		connectionsOut[i]->send(s);
	} 
	return true;
}

void Neuron::reset()
{
	for (int i=0; i<connectionsOut.size(); i++) 
	{
		connectionsOut[i]->reset();
	} 
}


ofstream& operator<<(ofstream& file, Neuron& newneuron)
{
  return file;
}
ifstream& operator>>(ifstream& file, Neuron& newneuron)
{
  return file;
}

void Neuron::start(int layer_index)
{
#ifndef FRESH_BRAIN
  if(!fork())
  {
    if ((shmid_running = shmget(key_running, SHM_RUNNING_SZ, 0666)) < 0) {
      perror("shmget");
      exit(1);
    }
    if ((shmid_onlayer = shmget(key_onlayer, SHM_ONLAYER_SZ, 0666)) < 0) {
      perror("shmget");
      exit(1);
    }
    if ((shmid_collected = shmget(key_collected, SHM_COLLECTED_SZ, 0666)) < 0) {
      perror("shmget");
      exit(1);
    }
    if ((shm_running = (char*)shmat(shmid_running, NULL, 0)) == (char *) -1) {
        cout << "error" << endl;
        perror("shmat");
        exit(1);
    }
    if ((shm_onlayer = (int*) shmat(shmid_onlayer, NULL, 0)) == (int *) -1) {
      perror("shmat");
      exit(1);
    }
    if ((shm_collected =(int*) shmat(shmid_collected, NULL, 0)) == (int *) -1) {
      perror("shmat");
      exit(1);
    }
    while(*shm_running)
    {
       if(*shm_onlayer==layer_index)
       {
         collect();
         ++(*shm_collected);
         usleep(100);
       }
       else {
         sleep(1);
       }
    }
    exit(0);
  }
  else {
//    cout << "skipped" << endl;
  }
#endif
}

void Neuron::adjust(char expected)
{
  //modifies the current bias of this neuron based on delta and eta, and then makes all of the neurons connected into it, adjust as well
  bias -= eta * getDelta(expected);
  for(int i=0; i<connectionsIn.size();i++)
  {
    connectionsIn[i]->adjust(expected);
  }
}

float Neuron::getOmega()
{
  //only calculate omega if it is equal to 0, otherwise just return it, this is meant to reduce redundancy
  omega = omega != 0.0f ?omega:sig(accumulated+bias);
  return omega;
}

float Neuron::getDelta(char expected)
{
  //again only caculate delta if it is equal to 0
  if(delta == 0.0f)
  {
    float sum = 0.0f;
    for(int i = 0; i<connectionsOut.size();i++)
    {
      //get the sum of all of the next neurons, modified by that connection's weight
      sum += ((Neuron*)allNeurons[connectionsOut[i]->getTo()])->getDelta(expected) * connectionsOut[i]->getWeight();
    }
    //set delta based on its partial derivative and the sum
    delta = getOmega()*(1-getOmega())*sum;
  }
  return delta;
}
