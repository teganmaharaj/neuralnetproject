#ifndef __SIGNAL__
#define __SIGNAL__

#include <fstream>
using namespace std;

/*
* Signals are created by Neurons when activated to send to other Neurons
* They are created with a signal strength
* They are then given to a Connection, which modifies their signal strength
* The connection then passes the signal to the next Neuron
*/
class Signal
{
private:
//Signal strength represents the amount of energy the signal has
  float strength;

public:
//CONSTRUCTORS
  Signal();
  Signal(const Signal&rhs);
  Signal(float str);
  virtual ~Signal();

//MUTATORS
  void weigh(float weight);

//ACCESSORS
  float get() const;

//OPERATORS
  bool operator==(const Signal& rhs) const;
  bool operator!=(const Signal& rhs) const;

  bool operator> (const Signal& rhs) const;
  bool operator>=(const Signal& rhs) const;
  bool operator< (const Signal& rhs) const;
  bool operator<=(const Signal& rhs) const;

  bool operator> (float str) const;
  bool operator>=(float str) const;
  bool operator< (float str) const;
  bool operator<=(float str) const;

  Signal& operator=(const Signal& rhs);
  Signal& operator=(float str);

//FRIENDS
  friend ifstream& operator>>(ifstream& file,Signal& rhs);
};
#endif
