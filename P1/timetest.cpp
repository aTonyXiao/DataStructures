#include <fstream>
#include "StackAr.h"
#include "StackLi.h"
#include "CursorList.h"
#include "LinkedList.h"
#include "SkipList.h"
#include "CPUTimer.h"
#include "QueueAr.h"

using namespace std;

vector<CursorNode<int> > cursorSpace(500001);

int getChoice();
void RunList(char *filename);
void RunCursorList(char *filename);
void RunStackAr(char *filename);
void RunStackLi(char *filename);
void RunQueueAr(char *filename);
void RunSkipList(char *filename);



int main(){
  char filename[80];
  int choice;
  CPUTimer ct;

  cout << "Filename >> ";
  cin >> filename;
  do
  {
    choice = getChoice();
    ct.reset();
    if (choice == 1)
        RunList(filename);
    if (choice == 2)
        RunCursorList(filename);
    if (choice == 3)
        RunStackAr(filename);
    if (choice == 4)
        RunStackLi(filename);
    if (choice == 5)
        RunQueueAr(filename);
    if (choice == 6)
        RunSkipList(filename);

    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while(choice > 0);

  return 0;
}




int getChoice()
{
  int choice;

  do{
    cout << "\n      ADT Menu" << endl;
    cout << "0. Quit" << endl;
    cout << "1. LinkedList" << endl;
    cout << "2. CursorList" << endl;
    cout << "3. StackAr" << endl;
    cout << "4. StackLi" << endl;
    cout << "5. QueueAr" << endl;
    cout << "6. SkipList" << endl;
    cout << "Your choice >> ";
    cin >> choice;
    if(choice < 0 || choice > 6)
    {
      cout << "Your choice is not between 1 and 6." << endl;
      cout << "Please try again." << endl;
    }
  } while (choice < 0 || choice > 6);
  return choice;
}


void RunList(char *filename)
{
  ifstream inf(filename);
  List <int> list;
  ListItr <int> listItr = list.zeroth();
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

  while(inf >> command >> value)
  {
    if (command == 'i')
    	list.insert(value,listItr);
		else
			list.remove(value);
  } 
} 


void RunCursorList(char *filename)
{
  ifstream inf(filename);
  CursorList <int> list(cursorSpace);
  CursorListItr <int> listItr = list.zeroth();
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

  while(inf >> command >> value)
  {
    if (command == 'i')
    	list.insert(value,listItr);
		else
			list.remove(value);
  } 
}



void RunStackAr(char *filename)
{
  ifstream inf(filename);
  StackAr <int> stack(500001);
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

  while(inf >> command >> value)
  {
    if (command == 'i')
    	stack.push(value);
		else
			stack.pop();
  }
}



void RunStackLi(char *filename)
{
  ifstream inf(filename);
  StackLi <int> stack;
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

  while(inf >> command >> value)
  {
    if (command == 'i')
    	stack.push(value);
		else
			stack.pop();
  }
}


void RunQueueAr(char *filename)
{
  ifstream inf(filename);
  Queue <int> queue(500001);
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

 while(inf >> command >> value)
  {
    if (command == 'i')
    	queue.enqueue(value);
		else
			queue.dequeue();
  }
}

void RunSkipList(char *filename)
{
  ifstream inf(filename);
  SkipList <int> list(0, 500001);
  char command, line[1000];
  int value;

  inf.getline(line, 1000);

  while(inf >> command >> value)
  {
    if (command == 'i')
      list.insert(value);
    else
      list.deleteNode(value);
  }
}




