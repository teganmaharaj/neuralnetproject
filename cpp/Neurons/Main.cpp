#ifndef __MAIN__
#define __MAIN__
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "System.h"
#include "Brain.h"
#include "Playground.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHM_RUNNING_SZ     1
#define SHM_ONLAYER_SZ     4
#define SHM_COLLECTED_SZ     4

int shmid_running;
int shmid_onlayer;
int shmid_collected;
key_t key_running=5678;
key_t key_onlayer=5768;
key_t key_collected=5876;
char *shm_running;
int *shm_onlayer;
int *shm_collected;

using namespace std;

Node ** allNeurons;
int neuralNetSize;
Connection ** allConnections;
int connectionSize;
float eta = 0.15f;

void run(int , char**);

int main(int argc, char ** argv)
{
  if ((shmid_running = shmget(key_running, SHM_RUNNING_SZ, IPC_CREAT | 0666)) < 0) {
     perror("shmget");
     exit(1);
  }
  if ((shmid_onlayer = shmget(key_onlayer, SHM_ONLAYER_SZ, IPC_CREAT | 0666)) < 0) {
     perror("shmget");
     exit(1);
  }
  if ((shmid_collected = shmget(key_collected, SHM_COLLECTED_SZ, IPC_CREAT | 0666)) < 0) {
     perror("shmget");
     exit(1);
  }

  if ((shm_running =(char*) shmat(shmid_running, NULL, 0)) == (char *) -1) {
    perror("shmat");
    exit(1);
  }
  if ((shm_onlayer =(int*) shmat(shmid_onlayer, NULL, 0)) == (int *) -1) {
    perror("shmat");
    exit(1);
  }
  if ((shm_collected =(int*) shmat(shmid_collected, NULL, 0)) == (int *) -1) {
    perror("shmat");
    exit(1);
  }
  *shm_running = 'a';
  *shm_onlayer = -1;
  *shm_collected = 0;
  run(argc,argv);
  *shm_running = '\0';
//  sys.off();
  //*shm_running = false;
  cout << "should quit:" << *shm_running << endl;
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
//  sys.off();
  theBrain.save(filename);
}
#endif
