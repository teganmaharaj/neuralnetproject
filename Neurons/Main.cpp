#ifndef __MAIN__
#define __MAIN__
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Brain.h"
#include "Playground.h"

using namespace std;

Node ** allNeurons;
int netSize;
Connection ** allConnections;
int connectionSize;
float eta = 0.1f;


int main(int argc, char ** argv)
{
  srand (time(NULL));
//should receive: filename of the brain(brainfile)
//                signal string(input neurons to be fired)
//                expected answer value(what the signals should represent)

  char* filename=argv[1];
  char* signals =argv[2];
  char  expected=argv[3][0];

  Playground thePlayground = Playground();
  Brain      theBrain      = Brain(&thePlayground);

  /*ifstream infile;
  infile.open(filename);
  if(infile.good()){
    infile.close();
    cout << "getting called" << endl;
    theBrain.setup(filename);
  }
  else{
    infile.close();
    theBrain.setup();
  }
  */
 cout << "start" << endl;
#ifdef FRESH_BRAIN
  cout << "makebrain" << endl;
  theBrain.setup();
  cout << "brainmade" << endl;
#else
  cout << "makebrain from file" << endl;
  theBrain.setup(filename);
  cout << "brainmaid" << endl;
//  cout << "OUTPUT SIZISIS" << thePlayground.size() << endl;
  theBrain.launch(signals);
  cout << "das launch has returned errorlessly" << endl;
  cout << "prep the parachute!" << endl;
  char answer=theBrain.land(expected);
//  cout << "The answer is: " << answer <<".\n";
  cout << "das net has landed errorlessly" << endl;
#endif
/*  cout << "yo bro what\'s up with that" << endl;
  cout << filename << endl;
*/theBrain.save(filename);/*
  Brain temp = Brain(thePlayground);
  temp.setup(filename);
  temp.save(filename);*/
  return 0;
}
#endif
