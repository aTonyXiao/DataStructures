#include <iostream>
#include <iomanip>

using namespace std;

template <class Comparable>
class BinaryTree
{
    Comparable object;
    BinaryTree<Comparable> *left;
    BinaryTree<Comparable> *right;
    
public:
    BinaryTree();
    BinaryTree(const Comparable &ob, BinaryTree<Comparable> *l,
               BinaryTree<Comparable> *r);
    bool operator< (const BinaryTree <Comparable> &rhs)const;
    void printTree(char encoding[], int count);
    const Comparable& getObject()const;
    
};


template <class Comparable>
BinaryTree<Comparable>::BinaryTree()
{
    left = NULL;
    right = NULL;
} // BinaryTree()

template <class Comparable>
BinaryTree<Comparable>::BinaryTree(const Comparable &ob, BinaryTree<Comparable> *l,
                                   BinaryTree<Comparable> *r) : object(ob), left(l), right(r)
{
} // BinaryTree()

template <class Comparable>
const Comparable& BinaryTree<Comparable>::getObject()const
{
    return object;
} // getObject()

template <class Comparable>
bool BinaryTree<Comparable>::operator< (const BinaryTree <Comparable> &rhs)const
{
    return object < rhs.object;
} // operator<


template <class Comparable>
void BinaryTree<Comparable>::printTree(char encoding[], int count)
{
    if(left) {
        encoding[count] = '0';
        left->printTree(encoding, count + 1);
    }
    
    if(right) {
        encoding[count] = '1';
        right->printTree(encoding, count + 1);
    }
    
    if(!left && !right) {
        cout << object << ' ';
        for(int i = 0; i < count; i++)
            cout << encoding[i];
        cout << endl;
    }
} // printTree()

class node {
    char character;
    int count;
    
public:
    bool operator > (const node &nd) const;
    bool operator < (const node &nd) const;
    
    node();
    node(const char cha, const int costcha);
    void setChar(char setcha);
    void setCount(int costcha);
    int getCount() const;
    friend ostream &operator << (ostream &os, const node &nd);
};

bool node::operator > (const node &nd) const{
    return count > nd.count;
}

bool node::operator < (const node &nd) const{
    return count < nd.count;
}

void node::setChar(char cha) {
    character = cha;
}

void node::setCount(int costcha) {
    count = costcha;
}

int node::getCount() const{
    return count;
}

node::node(){
    count = 0;
}

node::node(const char cha, const int costcha){
    character = cha;
    count = costcha;
}

ostream &operator << (ostream &os, const node &nd) {
    os << nd.character << setw(5) << nd.count;
    return os;
}

class BTreePtr {
    BinaryTree<node> *ptr;
public:
    BTreePtr(BinaryTree<node> *BTPtr = NULL): ptr(BTPtr){}
    bool operator < (const BTreePtr &rhs) const {return *ptr < *(rhs.ptr);}
    BinaryTree<node> *getPtr() {return ptr;}
};
