#ifndef __NEURON__
#define __NEURON__

#include "Signal.h"
#include "Node.h"
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
private:
//instance variables
  vector <Connection*> connectionsIn;
  vector <Connection*> connectionsOut;
  bool wasActivated;
  const static float threshold = 0.7f; //threshold potential for sending signal

public:
//constructors/destructors
  Neuron();
  //Neuron(vector <*Connection>, vector <*Connection>); //initializes the array of connections
  ~Neuron();

  bool receive();
  bool send(Signal&);
  void reset();

  friend ifstream& operator>>(ifstream&, Connection&);

};

#endif
