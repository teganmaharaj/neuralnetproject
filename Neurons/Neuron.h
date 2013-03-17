#ifndef __NEURON__
#define __NEURON__

#include "Signal.h"
#include "Node.cpp"
#include "Connection.h"
#include <vector>
#include <fstream>

/*
* Neurons are the main data type of the neural net
* They must receive and send signals from other neurals
* They must activate when excited, based on a function (tranh for example)
* They must they must modify their outgoing weights based on input by the Playground
* They can delete connections that drop below a threshold(become close to 0)
*/

using namespace std;

class Neuron: public Node
{
public:
//instance variables
  vector <Connection*> connectionsIn;
  vector <Connection*> connectionsOut;
protected:
  bool wasActivated;
  const static float threshold = 0.7f; //threshold potential for sending signal
  int counter;
  float accumulated;
public:
//constructors/destructors
  Neuron();
  //Neuron(vector <*Connection>, vector <*Connection>); //initializes the array of connections
  ~Neuron(){}

  bool receive(Signal&);
  bool send(Signal&);
  void reset();
  bool isActivated(){return wasActivated;};
  void reward(float);
  void punish(float);

  friend ifstream& operator>>(ifstream&, Connection&);

};

#endif
