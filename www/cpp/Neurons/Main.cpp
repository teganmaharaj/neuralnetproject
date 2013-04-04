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
float eta = 0.05f;

void run(int , char**);

int main(int argc, char ** argv)
{
#ifdef TRAIN
   for(int i=0;i<5;i++)
#endif
      run(argc,argv);
    return 0;
}

void run(int argc, char ** argv)
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

#ifdef FRESH_BRAIN
  cout << "makebrain" << endl;
  theBrain.setup();
  cout << "brainmade" << endl;
#else

  theBrain.setup(filename);
  theBrain.launch(signals);
  char answer=theBrain.land(expected);
#endif
  theBrain.save(filename);
}
#endif
