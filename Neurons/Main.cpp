#ifndef __MAIN__
#define __MAIN__
#include <iostream>
#include <fstream>
#include "Neuron.h"
#include "Brain.h"
#include "Playground.h"

using namespace std;

int main(int argc, char ** argv)
{
//should receive: filename of the brain(brainfile)
//                signal string(input neurons to be fired)
//                expected answer value(what the signals should represent)

char* filename=argv[0];
char* signals=argv[1];
char expected=argv[2][0];

Playground thePlayground = Playground();
Brain theBrain = Brain(thePlayground);

ifstream infile = ifstream(filename);
if(infile.good()){
  infile.close();
  theBrain.setup(filename);
}
else{
  infile.close();
  theBrain.setup();
}
theBrain.launch(signals);
char answer=thePlayground.land(expected);
cout<<"The answer is: " << answer <<".\n";
theBrain.save(filename);
return 0;
}
#endif
