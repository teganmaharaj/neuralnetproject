#include "Playground.h"

#include <fstream>
using namespace std;

Playground::Playground()
{
  olist=vector<OutputNeuron*>();
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
  allNeurons[i] = new OutputNeuron(*(allNeurons[i]),i, c);
  olist.push_back((OutputNeuron*)allNeurons[i]);
}


ifstream& operator>>(ifstream& file, Connection& c)
{
  file>>c.weight;
  file>>c.idFrom;
  file>>c.idTo;
  return file;
}

ofstream& operator<<(ofstream& file, Connection& c)
{
  file<<c.weight;
  file<<c.idFrom;
  file<<c.idTo;
  return file;
}

ofstream& operator<<(ofstream& file, Playground p)
{
  for(int i=0;i<p.olist.size();i++)
  {
    file<<p.olist[i]->getIndex();
    file<<p.olist[i]->getIdentifier();
  }
  return file;
}

#include "InputNeuron.h"
ofstream& operator<<(ofstream& file, InputNeuron& rhs)
{
  file<<rhs.index;
  return file;
}


char Playground :: land(char expected)
{
   int[] occurences= {0,0,0,0,0,0,0,0,0,0};
   
   for(int i=0;i<olist.size();i++)
   {
	if(olist[i]->isActivated())
		occurences[(int)(olist[i]->getIdentifier())-48]++;
   }
   int max=0;
   for(int i=0;i<10;i++)
   {
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

