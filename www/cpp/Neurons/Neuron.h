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

extern float eta;

class Neuron: public Node
{
public:
//instance variables
  vector <Connection*> connectionsIn;
  vector <Connection*> connectionsOut;
protected:
  float accumulated;//sum
public:
  float omega;//answer
  float delta;//error in answer
  float bias;
public:
//constructors/destructors
  Neuron();
//  Neuron(Node&);
  //Neuron(vector <*Connection>, vector <*Connection>); //initializes the array of connections
  ~Neuron(){}

  bool receive(Signal&);
  bool send(Signal&) const;
  void reset();
  void adjust(char);
  bool collect() const;

  float getAccumulated() const{return accumulated;};
  void setBias(float b){bias = b;};
  float getBias(){return bias;};

  float getOmega();
  float getDelta(char);

  friend ifstream& operator>>(ifstream&, Connection&);

};

#endif
