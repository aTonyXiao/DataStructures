//
//  main.cpp
//  Huffman Tries
//
//  Created  on 2/9/16.
//  Copyright © 2016 Jiapeng Zhong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BinaryTree.h"
#include "BinaryHeap.h"




using namespace std;

void readFile(ifstream &inf, int *list){
    char cha;
    while ((cha = inf.get()) != EOF) {
        list[(int)cha]++;
    }
}

void printList(const int *list) {
    char cha;
    int i = 0;
    while (i < 128)
    {
        if (list[i] != 0) {
            cha = char(i);
            cout << cha << " : " << list[i] << endl;
        }
        i++;
    }
}





void organizeList(int *raw, BinaryHeap<BTreePtr> &heap) {
    int i = 0;
    while ( i < 256)
    {
        if (raw[i]) {
            BinaryTree<node> *nd = new BinaryTree<node>(node(char(i), raw[i]), NULL, NULL);
            heap.insert(BTreePtr(nd));
        }
        i++;
    
    }
}

BTreePtr generateTree(BinaryHeap<BTreePtr> &heap) {
    BTreePtr left, right;
    node nd;
    while (!heap.isEmpty()) {
        left = heap.findMin();
        heap.deleteMin();
        if (heap.isEmpty())
            break;
        right = heap.findMin();
        heap.deleteMin();
        int leftcount = left.getPtr()->getObject().getCount();
        int rightcount = right.getPtr()->getObject().getCount();
        nd = node(char(0), leftcount + rightcount);
        BinaryTree<node> *tree = new BinaryTree<node>
        (nd, left.getPtr(), right.getPtr());
        heap.insert(BTreePtr(tree));
    }
    return left;
}

void printHeap(BinaryHeap<BinaryTree<node> > &heap) {
    while (!heap.isEmpty()) {
        cout << heap.findMin().getObject() << endl;
        heap.deleteMin();
    }
}

int main(int argc, const char * argv[]) {
    ifstream inf(argv[1]);
    int *rawList = new int[256];
    BinaryHeap<BTreePtr> heap(256);
    BTreePtr tree;
    char coding[256];
    int i = 0;
    while (i<256)
    {
    rawList[i] = 0;
        i++;
    }
    
    
    
    readFile(inf, rawList);
    organizeList(rawList, heap);
    
    tree = generateTree(heap);
    tree.getPtr()->printTree(coding, 0);
    return 0;
}
