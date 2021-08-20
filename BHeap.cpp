#include <iostream>
#include <stdlib.h>
using namespace std;

template<typename keytype>
struct Node
{
    keytype k;
    int treeType;
    Node* sibling;
    Node* child;
};

template<typename keytype>
class BHeap
{
    private:
        Node<keytype>* root;
        Node<keytype>* smallest;
        void destruct(Node<keytype>* d);
        void iinsert(keytype k);
        void meldEm(Node<keytype> *n);
        Node<keytype> *meld(Node<keytype>* a, Node<keytype>* b);
        void print(int isRoot, Node<keytype>* d);
        void copy(Node<keytype> * d, Node<keytype>* old, Node<keytype> * smallest);
        void doTheMeld(Node<keytype> *d);
        //void checker(Node<keytype> * d, int* checker, keytype parent);
    public:
        BHeap();
        BHeap(keytype k[], int s);
        BHeap &operator=(const BHeap &src); 
        BHeap(const BHeap &src);  
        ~BHeap();
        keytype peekKey();
        keytype extractMin();
        void insert(keytype k); 
        void merge(BHeap<keytype> &H2);
        void printKey();
        //void test();
};

template<typename keytype>
BHeap<keytype>::BHeap()
{
    smallest = NULL;
    root = NULL;
}

template<typename keytype>
BHeap<keytype>::BHeap(keytype k[], int s)
{
    smallest = NULL;
    root = NULL;
    
    for(int i = 0; i < s; i++)
    {
        iinsert(k[i]);
    }
}

template<typename keytype>
BHeap<keytype> &BHeap<keytype>::operator=(const BHeap &src)
{
    if(root != NULL)
    {
        destruct(root);
        smallest = NULL;
        root = NULL;
    }
    root = new Node<keytype>;
    Node<keytype>* old = src.root;
    smallest = NULL;
    copy(root, old, smallest);
    return *this;
}

template<typename keytype>
BHeap<keytype>::BHeap(const BHeap &src)
{
    root = new Node<keytype>;
    Node<keytype>* old = src.root;
    smallest = NULL;
    copy(root, old, smallest);
}

template<typename keytype>
BHeap<keytype>::~BHeap()
{
    if(root != NULL)
    {
        destruct(root);
    }
    smallest = NULL;
}

template<typename keytype>
keytype BHeap<keytype>::peekKey()
{
    return (*smallest).k;
}

template<typename keytype>
keytype BHeap<keytype>::extractMin()
{
    keytype returnValue = (*smallest).k;
    
    if(smallest == root)
    {
        root = root -> sibling;
    }
    else
    {
        Node<keytype>* l = root -> sibling;
        Node<keytype>* prev = root;
        while(l != smallest)
        {
            prev = l;
            l = l -> sibling;
        }

        prev -> sibling = l -> sibling;
    }
    
    Node<keytype>* curr = smallest -> child;
    doTheMeld(curr);

    delete(smallest);
    smallest = root;
    curr = root;
    while(curr != NULL)
    {
        if((*curr).k <= (*smallest).k)
        {
            smallest = curr;
        }
        curr = curr -> sibling;
    }

    return returnValue;
}

template<typename keytype>
void BHeap<keytype>::doTheMeld(Node<keytype>* d)
{
    if(d != NULL)
    {
        doTheMeld(d -> sibling);
        meldEm(d);
    }
}

template<typename keytype>
void BHeap<keytype>::insert(keytype k)
{
    iinsert(k);
}

template<typename keytype>
void BHeap<keytype>::merge(BHeap<keytype> &H2)
{
    Node<keytype>* curr = H2.root;
    while(curr != NULL)
    {
        Node<keytype>* target = curr;
        if(smallest != NULL)
        {
            if(smallest -> k > target -> k)
            {
                smallest = target;
            }
        }
        curr = curr -> sibling;
        target -> sibling = NULL;
        meldEm(target);
    }
    H2.root = NULL;
    H2.smallest = NULL;
}

template<typename keytype>
void BHeap<keytype>::printKey()
{
    Node<keytype> *d = root;
    while(d != NULL)
    {
        cout << "B" << (*d).treeType << endl;
        print(1, d);
        cout << endl << endl;
        d = d -> sibling;
    }
}

template<typename keytype>
void BHeap<keytype>::destruct(Node<keytype> *d)
{
    Node<keytype>* c = (*d).child;
    Node<keytype>* s = (*d).sibling;
    (*d).sibling = NULL;
    (*d).child = NULL;
    delete(d);
    if(c != NULL)
    {
        destruct(c);
    }
    if(s != NULL)
    {
        destruct(s);
    }
}

template<typename keytype>
void BHeap<keytype>::iinsert(keytype k)
{
    Node<keytype> *n = new Node<keytype>;
    (*n).k = k;
    (*n).treeType = 0;
    (*n).sibling = NULL;
    (*n).child = NULL;
    if(smallest == NULL || k < (*smallest).k)
    {
        smallest = n;
    }
    meldEm(n);
}

template<typename keytype>
void BHeap<keytype>::meldEm(Node<keytype> *n)
{
    n -> sibling = root;
    root = n;
    Node<keytype>* prev = NULL;
    int i = 0;
    while(n -> sibling != NULL && n -> treeType >= n -> sibling -> treeType)
    {
        i++;
        if(i > 50) break;
        if(n -> treeType == n -> sibling -> treeType)
        {
            Node<keytype>* oldSibling = n -> sibling -> sibling;
            Node<keytype>* g = meld(n, n -> sibling);
            g -> sibling = oldSibling;
            if(n == root)
            {
                root = g;
            }
            else
            {
                prev -> sibling = g;
            }
            
            n = g;
        }
        else
        {
            if(n == root)
            {
                root = n -> sibling;
                n -> sibling = n -> sibling -> sibling;
                root -> sibling = n;
                prev = root;
            }
            else
            {
                Node<keytype>* temp = n -> sibling -> sibling;
                prev -> sibling = n -> sibling;
                prev -> sibling -> sibling = n;
                prev = prev -> sibling;
                n -> sibling = temp;
            } 
        } 
    }
}

template<typename keytype>
Node<keytype> *BHeap<keytype>::meld(Node<keytype>* a, Node<keytype>* b)
{
    if((*a).k < (*b).k)
    {
        (*b).sibling = (*a).child;
        (*a).child = b;
        (*a).treeType++;
        return a;
    }
    else
    {
        (*a).sibling = (*b).child;
        (*b).child = a;
        (*b).treeType++;
        return b;
    }
}

template<typename keytype>
void BHeap<keytype>::print(int isRoot, Node<keytype>* d)
{
    cout << (*d).k << " ";
    if((*d).child != NULL)
    {
        print(0, (*d).child);
    }
    if((*d).sibling != NULL && isRoot == 0)
    {
        print(0, (*d).sibling);
    }
}

template<typename keytype>
void BHeap<keytype>::copy(Node<keytype>* n, Node<keytype>* o, Node<keytype> *smallest)
{

    n -> k = o -> k;
    n -> treeType = o -> treeType;
    n -> child = NULL;
    n -> sibling = NULL;

    if(smallest == NULL)
    {
        smallest = n;
    }

    if(smallest -> k > n -> k)
    {
        smallest = n;
    }

    if(o -> child != NULL)
    {
        Node<keytype>* g = new Node<keytype>;
        copy(g, o -> child, smallest);
        n -> child = g;
    }
    if(o -> sibling != NULL)
    {
        Node<keytype>* g = new Node<keytype>;
        copy(g, o -> sibling, smallest);
        n -> sibling = g;
    }
}
/*
template<typename keytype>
void BHeap<keytype>::test()
{
    int *c = new int;
    *c = 1;
    Node<keytype>* root1 = root;
    while(root1 != NULL)
    {
        checker(root1 -> child, c, root1 -> k);
        root1 = root1 -> sibling;
    }
    if(*c == 1)
    {
        cout << "It worked." << endl;
    }
    else
    {
        cout << "It did not work" << endl;
    }
}

template<typename keytype>
void BHeap<keytype>::checker(Node<keytype>* d, int* c, keytype parent)
{
    if(d == NULL)
    {
        return;
    }
    if((*d).k < parent)
    {
        cout << d -> k << " " << parent << endl;
        *c = 0;
    }
    if(d -> sibling != NULL)
    {
        checker(d -> sibling, c, parent);
    }
    if(d -> child != NULL)
    {
        checker(d -> child, c, d -> k);
    }
}
*/