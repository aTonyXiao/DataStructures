#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  BTreeNode *ptr = root->insert(value);
  if(ptr) // root split
  {
    InternalNode *IPtr = new InternalNode(internalSize, leafSize,
      NULL, NULL, NULL);
    IPtr->insert(root, ptr);
    root = IPtr;
  } // if root split
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()

//
//void Btree::remove2(int value)
//{
//    
//        int idx = remove(k);
//        
//                if (idx < n && keys[idx] == k)
//        {
//           if (leaf)
//                removeFromLeaf(idx);
//            else
//                removeFromNonLeaf(idx);
//        }
//        else
//        {
//            // If this node is a leaf node, then the key is not present in tree
//            if (leaf)
//            {
//                cout << "The key "<< k <<" is does not exist in the tree\n";
//                return;
//            }
//            
//                    bool flag = ( (idx==n)? true : false );
//            
//            
//            if (C[idx]->n < t)
//                fill(idx);
//            
//            if (flag && idx > n)
//                C[idx-1]->remove(k);
//            else
//                C[idx]->remove(k);
//        }
//    return;
//}

void BTree::remove(int value)
{
    BTreeNode *ptr;
    ptr = root->remove(value);
    
  if(ptr != NULL)
  {
    delete root;
//      cout << "1"<<endl;
    ptr->setParent(NULL);
      root = ptr;
  }
} // BTree::remove()
