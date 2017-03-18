// Author: Sean Davis 
// Created on January 1, 2016, 1:12 PM

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct
{
  char seat;
  int row;
}  Seat;

void writeBackToFront(ofstream &outf)
{
  int count, pos;
  Seat seats[48];
  for(int zone = 5; zone >= 0; zone--)
  {
    for(int i = 0; i < 8; i++)
      for(char j = 'A'; j <= 'F'; j++)
      {
        seats[i * 6 + j - 'A'].row = i + zone * 8 + 1;
        seats[i * 6 + j - 'A'].seat = j;
      }  // for each seat in the zone
    
    count = 48;
    
    for(int i = 0; i < 48; i++)
    {
      pos = rand() % count;
      outf << seats[pos].row << seats[pos].seat << ' ';
      seats[pos] = seats[--count];
    }  // for each seat in the zone
  }  // for each zone
  
  outf << endl;
}  // writeBackToFront()

void writeRandom(ofstream &outf)
{
  int pos, count = 0;
  Seat seats[288];
  
  for(int i = 0; i < 48; i++)
    for(char j = 'A'; j <= 'F'; j++)
    {
      seats[count].row = i + 1;
      seats[count++].seat = j;
    } // for each seat
  
  for(int i = 0; i < 288; i++)
  {
    pos = rand() % count;
    outf << seats[pos].row << seats[pos].seat << ' ';
    seats[pos] = seats[--count];
  }
  
  outf << endl;
} // writeRandom()


void writeOutsideIn(ofstream &outf)
{
  int count = 0, pos;
  int rows[96];
  
  for(int row = 1; row <= 48; row++)
  {
    rows[count++] = row;
    rows[count++] = row + 100;
  }
  
  for(int i = 0; i < 96; i++)
  {
    pos = rand() % count;
    if(rows[pos] < 100)
      outf << rows[pos] << 'A' << ' ';
    else
      outf << rows[pos] - 100 << 'F' << ' ';
    
    rows[pos] = rows[--count];
  }  // for each seat in window zone
  
  // count should be zero
  
  for(int row = 1; row <= 48; row++)
  {
    rows[count++] = row;
    rows[count++] = row + 100;
  }
  
  for(int i = 0; i < 96; i++)
  {
    pos = rand() % count;
    if(rows[pos] < 100)
      outf << rows[pos] << 'B' << ' ';
    else
      outf << rows[pos] - 100 << 'E' << ' ';
    
    rows[pos] = rows[--count];
  }  // for each seat in middle zone
  
  // count should be zero 
  for(int row = 1; row <= 48; row++)
  {
    rows[count++] = row;
    rows[count++] = row + 100;
  }
  
  for(int i = 0; i < 96; i++)
  {
    pos = rand() % count;
    if(rows[pos] < 100)
      outf << rows[pos] << 'C' << ' ';
    else
      outf << rows[pos] - 100 << 'D' << ' ';
    
    rows[pos] = rows[--count];
  }  // for each seat in window zone
 
  outf << endl;
}  // writeOutsideIn()


int main() 
{
  int seed, count, pos, planePos;
  cout << "Seed: ";
  cin >> seed;
  srand(seed);
  char filename[80];
  sprintf(filename, "passengers-%d.txt", seed);
  ofstream outf(filename);
  planePos = 0;
  
  writeBackToFront(outf);
  writeRandom(outf);
  writeOutsideIn(outf);
  outf.close();
  return 0;
} // main())

