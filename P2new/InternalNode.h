#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  BTreeNode* addPtr(BTreeNode *ptr, int pos);
  void addToLeft(BTreeNode *last);
  void addToRight(BTreeNode *ptr, BTreeNode *last);
  void addToThis(BTreeNode *ptr, int pos); // pos is where the node should go
  int getMaximum()const;
  int getMinimum()const;
  InternalNode* insert(int value); // returns pointer to new
    // InternalNode if it splits else NULL
  void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  void print(Queue <BTreeNode*> &queue);
  void resetMinimum(const BTreeNode* child);
    InternalNode* rmSibling();
            BTreeNode* remove(int value);
            BTreeNode* rmChild(int position);
            InternalNode* rmLSibling();
            InternalNode* rmRSibling(int postion);

            InternalNode* split(BTreeNode *last);
}; // InternalNode class



#endif
