#ifndef __NEURON__
#define __NEURON__

#include "Signal.h"
#include <fstream>

using namespace std;

/*
* Neurons are the main data type of the neural net
* They must receive and send signals from other neurals
* They must activate when excited, based on a function (tranh for example)
* They must they must modify their outgoing weights based on input by the Playground
* They can delete connections that drop below a threshold(become close to 0)
*/
class Neuron
{

private:
//instance variables
  vector <*Connection> connectionsIn;
  vector <*Connection> connectionsOut;
  boolean wasActivated;
  const threshold = 0.7; //threshold potential for sending signal

public:
//constructors/destructors
  Neuron();
  //Neuron(vector <*Connection>, vector <*Connection>); //initializes the array of connections
  ~Neuron();

  bool receive();
  bool send(Signal&);
  void reset();

  friend ofstream& operator<<(ofstream&, Neuron&);
  friend ifstream& operator>>(ifstream&, Neuron&);

};

#endif
