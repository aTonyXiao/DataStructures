#include <iostream>
#include <fstream>
#include "CPUTimer.h"
#include "NetDriver.h"
#include "maxfinder.h"

int main(int argc, char* argv[])
{
  int numComputers, numTerminals, numEdges;
  CPUTimer ct;

  ifstream inf(argv[1]);
  inf >> numComputers >> numTerminals >> numEdges;
  Computer *computers = new Computer[numComputers];
  Edge *edges = new Edge[numEdges];

  for(int i = 0; i < numComputers; i++)
    inf >> computers[i].address;

  for(int i = 0; i < numEdges; i++)
    inf >> edges[i].src >> edges[i].dest >> edges[i].capacity;

  ct.reset();
  MaxFinder *maxFinder = new MaxFinder(computers, numComputers,numTerminals);
  delete [] computers;
  int flow = maxFinder->calcMaxFlow(edges, numEdges);
  cout << "CPU: " << ct.cur_CPUTime() << " Flow: " << flow << endl;
  return 0;
} // main()

