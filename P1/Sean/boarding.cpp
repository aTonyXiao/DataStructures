// Author: Sean Davis 
// Created on January 1, 2016, 2:01 PM

#include <fstream>
#include <iostream>
#include "QueueAr.h"
#include "StackAr.h"
using namespace std;
typedef enum {NONE, STOWING_LUGGAGE1, STOWING_LUGGAGE2, MOVING_AC_OUT, 
  MOVING_DF_OUT, MOVING_AC_IN, MOVING_DF_IN,  MOVING_PASSENGER} State;
  

class Row
{
public:
  StackAr <char> stackAC, stackDF, stackAisle;
  char passengerSeat;
  int passengerRow;
  int rowNum;
  State state;
  Row() : stackAC(3), stackDF(3), stackAisle(2), passengerRow(0), state(NONE) {}
};  // class Row

void initializePlane(Queue <Row> &plane)
{
  plane.makeEmpty();
  Row row;
  
  for(int i = 48; i > 0; i--)
  {
    row.rowNum = i;
    plane.enqueue(row);
  }  // make each row empty
}  // initializePlane()

int loadPassengers(Queue <Row> &plane, ifstream &inf)
{
  int time = 0, loadedCount = 0, seatedCount = 0;
  Row row, lastRow;
  
  while(seatedCount < 288)
  {
    lastRow.rowNum = 0;
 
    for(int rowNum = 48; rowNum >= 1; rowNum--)
    {
      row = plane.dequeue();
      
      switch(row.state)
      {
        case NONE:
          if(row.passengerRow > 0)
          {
            if(row.passengerRow == row.rowNum)
              row.state = STOWING_LUGGAGE1;
            else // passenger after row  
              if(lastRow.rowNum > 0)
                if(lastRow.passengerRow == 0)
                {
                  lastRow.passengerRow = row.passengerRow;
                  lastRow.passengerSeat = row.passengerSeat;
                  row.passengerRow = 0;
                }
          } // if have a passenger this row      
          break;
        case STOWING_LUGGAGE1: row.state = STOWING_LUGGAGE2; break;
        case STOWING_LUGGAGE2:
          if(row.passengerSeat < 'D')
            if(!row.stackAC.isEmpty() && row.stackAC.top() > row.passengerSeat)
            {
              row.stackAisle.push(row.stackAC.topAndPop());
              row.state = MOVING_AC_OUT;
            }
            else // nothing larger in AC stack
            {
              row.stackAC.push(row.passengerSeat);
              row.state = NONE;
            }  // else nothing larger in AC stack
          else // passenger Seat > 'C'
            if(!row.stackDF.isEmpty() && row.stackDF.top() < row.passengerSeat)
            {
              row.stackAisle.push(row.stackDF.topAndPop());
              row.state = MOVING_DF_OUT;
            }
            else // nothing larger in AC stack
            {
              row.stackDF.push(row.passengerSeat);
              row.state = NONE;
            }  // else nothing larger in AC stack
          break;
        case MOVING_AC_OUT: 
           if(!row.stackAC.isEmpty() && row.stackAC.top() > row.passengerSeat)
            {
              row.stackAisle.push(row.stackAC.top());
              row.stackAC.pop();
            }
            else // nothing larger in AC stack
            {
              row.stackAC.push(row.passengerSeat);
              
              if(!row.stackAisle.isEmpty())
                row.state = MOVING_AC_IN;
              else
                row.state = NONE;
            }  // else nothing larger in AC stack
           break;
        case MOVING_DF_OUT: 
          if(!row.stackDF.isEmpty() && row.stackDF.top() < row.passengerSeat)
            {
              row.stackAisle.push(row.stackDF.top());
              row.stackDF.pop();
            }
            else // nothing larger in AC stack
            {
              row.stackDF.push(row.passengerSeat);
              
              if(!row.stackAisle.isEmpty())
                row.state = MOVING_DF_IN;
              else
               row.state = NONE;
            }  // else nothing larger in AC stack
           break;
        case MOVING_AC_IN: 
          row.stackAC.push(row.stackAisle.topAndPop());
          
          if(row.stackAisle.isEmpty())
            row.state = NONE;  // otherwise stay MOVING_AC_IN

          break;
        case MOVING_DF_IN: 
          row.stackDF.push(row.stackAisle.topAndPop());
          
          if(row.stackAisle.isEmpty())
            row.state = NONE;  // otherwise stay MOVING_AC_IN

          break;
      }
      
      if(row.state == NONE && row.passengerRow == row.rowNum)
      {
        row.passengerRow = 0;  // emptied sentinel
        seatedCount++;
      }
      
      if(lastRow.rowNum > 0)
        plane.enqueue(lastRow);
      
      lastRow = row;
    } // for each row
   
    if(lastRow.passengerRow == 0 && loadedCount < 288) // empty first row
    {
      inf >> lastRow.passengerRow;
      inf >> lastRow.passengerSeat;
      loadedCount++;
    }
    
    plane.enqueue(lastRow);
    time += 5;
  } // for each passenger to board this plane
  
  return time;
}  // loadPassengers()


int main(int argc, char** argv) 
{
  Queue <Row> plane(48);
  ifstream inf(argv[1]);
  
  for(int i = 0; i < 3; i++)
  {
    initializePlane(plane);
    int time = loadPassengers(plane, inf);
    
    switch (i)
    {
      case 0: cout << "Back to front: "; break;
      case 1: cout << "Random: "; break;
      default: cout << "Outside in: "; break;
    }  // switch
    
    cout << time << endl;
  }
  
  return 0;
} // main())

