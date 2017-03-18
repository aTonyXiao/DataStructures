#include <iostream>
#include <cstring>
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "computer.h"
using namespace std;

static int tableSize;

  for(i = 0; i < lastPos; i++)
  {
    hashVal = 0;

      const char *ptr = computer[i].address;
      while (*ptr)
      {
          hashVal = hashVal * 37 + *ptr;
          ptr++;
      }

    hashVal %= tableSize;
    if(hashVal < 0)
        hashVal += tableSize;
      
    while(computerPos[hashVal].pos != -1)
//      hashVal = (++hashVal) % tableSize;
    {
        if (hashVal<tableSize)
            hashVal++;
        else
            hashVal = (hashVal%tableSize) + 1;
    
    }
  } // for each computer
} // MaxFinder()


int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{
  saveEdge(edges, numEdges);
  BinaryHeap heap(numEdges);
  Flow flow;
  int back, flowAmt, i = 1, j = 0;
  Computer2 *cptr, *cptr2, **q = new Computer2* [numComp];

//   while (1)
//   {
//       if (i>numComp)
//           break;
//       computers[i].kn = true;
//       i++;
//   }
    
    
    
  for(i = 1; i <= numEnd; i++)
    computers[i].known = true;

  while(1)
  {
    heap.currentSize = 0;
    back = 0;

    for(i = 1; i <= numEnd; i++) // put terminals in
    {
      cptr = &computers[i];
        j = 0;
        while (j < cptr->forwardCount)
        {
            if(cptr->forwardCapacities[j] > 0
               && cptr->forwardVertices[j]->flow < cptr->forwardCapacities[j])
            {
                heap.insert(Flow(cptr->forwardVertices[j],
                                 cptr->forwardCapacities[j]));
                cptr->forwardVertices[j]->flow = cptr->forwardCapacities[j];
                cptr->forwardVertices[j]->prev = cptr;
                q[back++] = cptr->forwardVertices[j];
            }
            j++;
        
        }
    }  // for each terminal

      
//      calculateflow(heap);
      
      
      
    while(heap.currentSize > 0)
    {
      heap.deleteMax(flow);
      cptr = flow.cptr;
      if (cptr == computers)
        break; // reached sink
              
              while (!terminals.isEmpty()) {
                  Computer temp = terminals.dequeue();
                  do {
                      flow = Flow(temp.address, edges, &numEdges, INT_MAX, -1, depth);
                      totalFlow += flow;
                  } while (flow != 0);
              }

            if(cptr2->flow < flowAmt)
            {
              if(cptr2->flow == 0)
                q[back++] = cptr2;

              cptr2->flow = flowAmt;
              cptr2->prev = cptr;
              heap.insert(Flow(cptr2, cptr2->flow));
            }  // if better flow
          } // if not known
            i++;
        } // for each forwardVertices

//        for(i = 0; i < cptr->backFlowCount; i++) // for back flows
//          if(cptr->backFlows[i] > 0)
//          {
//            cptr2 = cptr->backVertices[i];
//            if(!cptr2->known)
//            {
//              if(cptr->backFlows[i] < cptr->flow)
//                flowAmt = cptr->backFlows[i];
//              else
//                flowAmt = cptr->flow;
//
//              if(cptr2->flow < flowAmt)
//              {
//                if(cptr2->flow == 0)
//                  q[back++] = cptr2;
//
//                cptr2->flow = flowAmt;
//                cptr2->prev = cptr;
//                heap.insert(Flow(cptr2, cptr2->flow));
//              }  // if better flow
//            } // if not known
//          } // if a back flow
      }  // if not known
    } // while more in heap

    if(cptr != computers) // didn't reach sink so done
      break;

    savePath();

    for(i = 0; i < back; i++)
    {
      q[i]->flow = 0;
      q[i]->known = false;
    } // for each node in queue

  } // while more paths

  return totalFlow;
} // calcMaxFlow()

void MaxFinder::calculateflow(BinaryHeap heap)
{
//        while(heap.>flow == 0)
//                    q[back++] = cptr2;
//    
//                  cptr2->flow = flowAmt;
//                  cptr2->prev = cptr;
//                  heap.insert(Flow(cptr2, cptr2->flow));
                }  // if better flow
              } // if not known
            } // fo
                      q[back++] = cptr2;
    
                }  // if better flow
//              a back flow
//          }  // if not known
//        } // while more in heap
//}



int MaxFinder:: fllow(char *address, Edge *edges, int *numEdges, int curFlow, int curIndex, int depth) {
    int flow2 = curFlow, maxIndex = -1;
    char *newAddress;
    for (int i = 0; i < *numEdges; i++) {
        if (strcmp(edges[i].src, address) == 0) {
            if (edges[i].capacity > maxFlow) {
                maxFlow = edges[i].capacity;
                maxIndex = i;
            }
        }
    }
    
    if (maxIndex >= 0) {
        newAddress = edges[maxIndex].dest;
    } else {
        edges[curIndex].capacity -= curFlow;
        *numEdges += 1;
        Edge *newEdges = new Edge[*numEdges];
        for (int i = 0; i < *numEdges - 1; i++)
            newEdges[i] = edges[i];
        
        edges = newEdges;
        Edge temp;
        strcpy(temp., edges[curIndex].dest);
        strcpy(temp.dest, edges[curIndex].src);
        temp.capacity = curFlow;
        edges[curIndex] = temp;
        return curFlow;
    }
    if (maxFlow < curFlow)
        flow = curFlow;
//
    flow = Flow(newAddress, edges, numEdges, flow, maxIndex, depth - 1);
    edges[curIndex].capacity -= curFlow;
    *numEdges += 1;
    Edge *newEdges = new Edge[*numEdges];
    for (int i = 0; i < *numEdges - 1; i++)
        newEdges[i] = edges[i];
    
    edges = newEdges;
    Edge temp;
    strcpy(temp.src, edges[curIndex].dest);
    strcpy(temp.dest, edges[curIndex].src);
    temp.capacity = curFlow;
    edges[curIndex] = temp;
    
    return 0;
}

void MaxFinder::saveEdge(Edge *edges, int numEdges, char* ptr){

    int i;
    for (i = 0; i < numEdges; i++);
        terminals.enqueue(computers[i]);
    stations = computers;
    num_Computers = numComputers;
    num_Terminals = numTerminals;
        cout<< ptr << endl;

    
}


void MaxFinder::saveEdge(Edge *edges, int numEdges)
{
  int hashVal, beginfrom, endWith, i;
//  int maxEdges = 0;
  for(i = 0; i < numEdges; i++)
  {
    hashVal = 0;
    for(const char *ptr = edges[i].src; *ptr; ptr++)
      hashVal = hashVal * 37 + *ptr;

    hashVal %= tableSize;
    if(hashVal < 0)
      hashVal += tableSize;
      hashVal = 0;
    for(const char *ptr = edges[i].dest; *ptr; ptr++)
      hashVal = hashVal * 37 + *ptr;

    hashVal %= tableSize;
    if(hashVal < 0)
      hashVal += tableSize;

    } // if not terminal as destination
  } // for each edge

} // saveEdge()

void MaxFinder::savePath()
{

      while (i < cptr->forwardCount )
      {
          Computer2 *tmp = cptr->forwardVertices[i];
          if(tmp == cptr->prev) // previous used a back flow
              cptr->forwardCapacities[i] += flowAmt;
          
          if(tmp == next) // used a forward edge
              cptr->forwardCapacities[i] -= flowAmt;

          i++;
      }
    next = cptr;
    cptr = cptr->prev;
  }  // while haven't reached terminal
} // savePath()

