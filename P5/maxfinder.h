#include "NetDriver.h"
#include "computer.h"



class MaxFinder
{
  Computer2 *computers;
  int numComp;
  int numEnd;
//  int tableSize;
  int totalFlow;
  void saveEdge(Edge *edges, int numEdges, char* ptr);
  void savePath();
public:
  MaxFinder(const Computer *computers, int numComp, int numEnd);

  int fllow(char *address, Edge *edges, int *numEdges, int
            curFlow, int curIndex, int depth);
}; // class MaxFinder


class BinaryHeap
{
public:
    bool isEmpty( ) const;
    bool isFull( ) const;
    const Flow & findMax( ) const;
    
    void insert( const Flow & x );

    
    int  currentSize;  // Number of elements in heap
    int capacity;
    void buildHeap( );
    void percolateDown( int hole );
};
