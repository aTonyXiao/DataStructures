#ifndef COMPUTER_H
  #define COMPUTER_H

#define MAX_VERTICES 15

struct Computer2
{
  //char address[16];
  Computer2* forwardVertices[MAX_VERTICES];
  unsigned char forwardCapacities[MAX_VERTICES];
  unsigned char backFlows[MAX_VERTICES];
  Computer2* backVertices[MAX_VERTICES];
  unsigned char forwardCount;
  unsigned char backFlowCount;
  Computer2 *prev;
  short flow;
  bool known;
  Computer2():forwardCount(0), backFlowCount(0), prev(0), flow(0), known(false){}
};

struct ComputerPos
{
  char address[16];
  short pos;
  ComputerPos():pos(-1){}
};

struct Flow
{
  Computer2* cptr;
  short flow;
  Flow(){}
  Flow(Computer2 *c,  short f): cptr(c), flow(f) {}
};
#endif

 
