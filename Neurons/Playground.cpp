#include "Playground.h"
#include <iostream>
#include <fstream>
using namespace std;

Playground::Playground()
{
  olist = vector<OutputNeuron*>();
}
Playground::Playground(const Playground& rhs)
{
  for(int i=0;i<rhs.olist.size();i++)
  {
    olist.push_back(rhs.olist[i]);
  }
}

void Playground::addOutput(int i, char c)
{
  delete  allNeurons[i];
  allNeurons[i] = new OutputNeuron(i, c);
  olist.push_back((OutputNeuron*)allNeurons[i]);
  cout << "OLIST SIZE" << olist.size() << endl;	
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  file>>c.from;
  file>>c.to;
  file>>c.weight;
  ((Neuron*)(allNeurons[c.from]))->connectionsOut.push_back(&c);
  ((Neuron*)(allNeurons[c.to]))  ->connectionsIn.push_back(&c);
  return file;
}

ofstream& operator<<(ofstream& file, Connection& c)
{
  #ifdef verbose_output_file
  file<<"From ";
  file<<c.from;
  file<<" to ";
  file<<c.to;
  file<<" : "; 
  file<<c.weight;
  #else
  file<<c.from;
  file<<"\t";
  file<<c.to;
  file<<"\t";
  file<<c.weight;
  #endif
  return file;
}

ofstream& operator<<(ofstream& file, Playground p)
{
  #ifdef verbose_output_file
  file << "outputsize";
  #endif
  file << p.olist.size();
  #ifdef verbose_output_file
  file << " above";
  #endif
  file << "\n";
  for(int i=0;i<p.olist.size();i++)
  {
    #ifdef verbose_output_file
    file << "index ";
    #endif
    file << p.olist[i]->getIndex();
    file << " ";
    #ifdef verbose_output_file
    file << "id ";
    #endif
    file << p.olist[i]->getIdentifier();
    file << "\n";
  }
  return file;
}

#include "InputNeuron.h"
ofstream& operator<<(ofstream& file, InputNeuron& rhs)
{
  file << rhs.index;
  return file;
}


char Playground :: land(char expected)
{
   int occurences[]= {0,0,0,0,0,0,0,0,0,0};
   cout << "OLIST SIZE" << olist.size() << endl;
   for(int i=0;i<olist.size();i++)
   {
	if(olist[i]->isActivated())
		occurences[(int)(olist[i]->getIdentifier())-48]++;
   }
   int max=0;
   for(int i=0;i<10;i++)
   {
	std::cout << occurences[i] << std::endl;
	if(occurences[i]>max)
		max=occurences[i];
   }
   char answer=(char)(max+48);
   for(int i=0;i<olist.size();i++)
   {
	if(olist[i]->getIdentifier()==expected && olist[i]->isActivated())
		olist[i]->reward(1.01);
	else
		olist[i]->punish(0.98);
   }
   return answer;
}  

