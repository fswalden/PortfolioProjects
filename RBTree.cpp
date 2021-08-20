#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


template <typename keytype, typename valuetype>
class Node
{
    private:
        keytype k;
        valuetype v;
    public: 
        Node();
        Node(keytype k, valuetype v);
        ~Node();
        Node &operator=(const Node &src); 
        Node(const Node &src);  
        keytype* key();
        valuetype* value();
        void setKey(keytype x);
        void setValue(valuetype x);
        int below;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        string color;
        void copy(Node<keytype, valuetype>* x, Node<keytype, valuetype> *nil, Node<keytype, valuetype> *nnil);
        Node<keytype, valuetype> *Nsearch(keytype x, Node<keytype, valuetype> *nil);
        int findRank(keytype x, Node<keytype, valuetype> *nil);
        Node<keytype, valuetype>* select(int pos, Node<keytype, valuetype> *nil);
        void preorder(Node<keytype, valuetype> *nil); 
        void inorder(Node<keytype, valuetype> *nil); 
        void inorder2(keytype* a, int* s, Node<keytype, valuetype> *nil); 
        void postorder(Node<keytype, valuetype> *nil);
        void printk(int x, int *d, Node<keytype, valuetype> *nil);
};

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node()
{
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
    below = 1;
    color = "red";
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node(keytype k1, valuetype v1)
{
    k = k1;
    v = v1;
    below = 1;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
    color = "red";
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::~Node()
{
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype> & Node<keytype, valuetype>::operator=(const Node &src) 
{
    leftChild = src.leftChild;
    rightChild = src.rightChild;
    parent = src.parent;
    color = src.color;
    below = src.below;
    k = *(src.key());
    v = *(src.value());
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>::Node(const Node &src)
{
    leftChild = src.leftChild;
    rightChild = src.rightChild;
    parent = src.parent;
    color = src.color;
    below = src.below;
    k = *(src.key());
    v = *(src.value());
}

template <typename keytype, typename valuetype>
keytype* Node<keytype, valuetype>::key()
{
    return &k;
}

template <typename keytype, typename valuetype>
valuetype* Node<keytype, valuetype>::value()
{
    return &v;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::setKey(keytype x)
{
    k = x;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::setValue(valuetype x)
{
    v = x;
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::copy(Node<keytype, valuetype>* x, Node<keytype, valuetype> *nil, Node<keytype, valuetype> *nnil)
{
    k = *((*x).key());
    v = *((*x).value());
    color = (*x).color;
    below = (*x).below;

    if((*x).leftChild != nil)
    {
        Node* left = new Node<keytype, valuetype>();
        leftChild = left;
        (*left).parent = this;
        (*left).copy((*x).leftChild, nil, nnil);
    }
    else
    {
        leftChild = nnil;;
    }
    
    if((*x).rightChild != nil)
    {
        Node* right = new Node<keytype, valuetype>();
        rightChild = right;
        (*right).parent = this;
        (*right).copy((*x).rightChild, nil, nnil);
    }
    else
    {
        rightChild = nnil;
    }
    
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::Nsearch(keytype x, Node<keytype, valuetype> *nil)
{
    if(x == k)
    {
        return this;
    }
    else if(x > k)
    {
        if(rightChild == nil)
        {
            return nil;
        }
        else
        {
            return (*rightChild).Nsearch(x, nil);
        } 
    }
    else
    {
        if(leftChild == nil)
        {
            return nil;
        }
        else
        {
            return (*leftChild).Nsearch(x, nil);
        } 
    }
}

template <typename keytype, typename valuetype>
int Node<keytype, valuetype>::findRank(keytype x, Node<keytype, valuetype> *nil)
{
    /*
    if(k == x)
    {
        if(leftChild == nil)
        {
            return 1;
        }
        else
        {
            return 1 + (*leftChild).below;
        }
    }
    else if(x < k)
    {
        if(leftChild == nil)
        {
            return 0;
        }
        else
        {
            return (*leftChild).findRank(x, nil);
        }
    }
    else
    {
        if(rightChild == nil)
        {
            return 0;
        }
        else
        {
            if(leftChild == nil)
            {
                return 1 + (*rightChild).findRank(x, nil);
            }
            else
            {
                return 1 + (*leftChild).below + (*rightChild).findRank(x, nil);
            }
            
        }
        
    }*/
    
    int r = (*leftChild).below + 1;
    Node<keytype, valuetype> *y = this;
    while((*y).parent != nil)
    {
        if(y == (*(*y).parent).rightChild)
        {
            r = r + 1 + (*(*(*y).parent).leftChild).below;
        }
        y = y->parent;
    }
    return r;
    
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Node<keytype, valuetype>::select(int pos, Node<keytype, valuetype> *nil)
{
    /*
    int leftInclusive = 1;
    if(leftChild != nil)
    {
        leftInclusive += (*leftChild).below;
    }
    if(leftInclusive == pos)
    {
        return this;
    }
    else if(leftInclusive > pos)
    {
        return (*leftChild).select(pos, nil);
    }
    else
    {
        return (*rightChild).select(pos - leftInclusive, nil);
    }*/
    //cout << nil -> below << endl;
    int r = (*leftChild).below + 1;
    if(pos == r)
    {
        return this;
    }
    else if(pos < r)
    {
        return (*leftChild).select(pos, nil);
    }
    else
    {
        return (*rightChild).select(pos - r, nil);
    }
    
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::preorder(Node<keytype, valuetype> *nil)
{
    //cout << "(" << k << ", " << below << ")";
    cout << k << " ";
    if(leftChild != nil)
    {
        (*leftChild).preorder(nil);
    }
    if(rightChild != nil)
    {
        (*rightChild).preorder(nil);
    }
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::inorder(Node<keytype, valuetype> *nil)
{
    if(leftChild != nil)
    {
        (*leftChild).inorder(nil);
    }
    cout << k << " ";
    if(rightChild != nil)
    {
        (*rightChild).inorder(nil);
    }
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::postorder(Node<keytype, valuetype> *nil)
{
    if(leftChild != nil)
    {
        (*leftChild).postorder(nil);
    }
    if(rightChild != nil)
    {
        (*rightChild).postorder(nil);
    }
    cout << k << " ";
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::printk(int x, int* d, Node<keytype, valuetype> *nil)
{
    if(leftChild != nil)
    {
        (*leftChild).printk(x, d, nil);
    }
    if(*d < x)
    {
        cout << k << " ";
        *d = *d + 1;
    }
    else
    {
        return;
    }
    if(rightChild != nil && *d <= x)
    {
        (*rightChild).printk(x, d, nil);
    }
}

template <typename keytype, typename valuetype>
void Node<keytype, valuetype>::inorder2(keytype* a, int* s, Node<keytype, valuetype> *nil)
{
    if(leftChild != nil)
    {
        (*leftChild).inorder2(a, s, nil);
    }
    a[*s] = k;
    (*s) += 1;
    if(rightChild != nil)
    {
        (*rightChild).inorder2(a, s, nil);
    }
}

template <typename keytype, typename valuetype>
class RBTree
{
    private:
        Node<keytype, valuetype>* root;
        int siz;
        //int f;
        Node<keytype, valuetype> * nil;
        void destruct(Node<keytype, valuetype>* d);
        void leftRotate(Node<keytype, valuetype> *d);
        void rightRotate(Node<keytype, valuetype> *d);
        void insertFix(Node<keytype, valuetype> *d);
        //void checker(Node<keytype, valuetype>* x, int bc, int* array, int* t, int* c, keytype* b, int* s);
        void transplant(Node<keytype, valuetype>* u, Node<keytype, valuetype>* v);
        void deleteFixup(Node<keytype, valuetype>* x);
        void iinsert(keytype k, valuetype v);
        void belowFix(Node<keytype, valuetype> *n);
        void belowFix2(Node<keytype, valuetype> *n);
        int getRank(keytype k);
        Node<keytype, valuetype>* treeMax(Node<keytype, valuetype>* n);
        Node<keytype, valuetype>* getPred(keytype k);
    public:
        RBTree();
        RBTree(keytype k[], valuetype V[], int s);
        ~RBTree();
        RBTree &operator=(const RBTree &src); 
        RBTree(const RBTree &src);  
        valuetype * search(keytype k);
        void insert(keytype k, valuetype v);
        int remove(keytype k);
        int rank(keytype k);
        keytype select(int pos);
        keytype *successor(keytype k);
        keytype *predecessor(keytype k);
        int size() const;
        void preorder(); 
        void inorder(); 
        void postorder();
        void printk(int k);
        //int test(); //////// DELETE THIS********** ///////
};

template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree()
{
    nil = new Node<keytype, valuetype>;
    (*nil).color = "black";
    (*nil).below = 0;
    //(*nil).rightChild = nil;
    //(*nil).leftChild = nil;
    //(*nil).parent = nil;
    root = nil;
    root -> parent = nil;
    siz = 0;
}

template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s)
{
    siz = 0;
    nil = new Node<keytype, valuetype>;
    (*nil).color = "black";
    (*nil).below = 0;
    root = nil;
    root -> parent = nil;
    for(int i = 0; i < s; i++)
    {
        iinsert(k[i], V[i]);
    }
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::destruct(Node<keytype, valuetype>* d)
{
    if(d == nil || d == NULL)
    {
        return;
    }
    if((*d).rightChild != nil)
    {
        Node<keytype, valuetype> *right = (*d).rightChild;
        destruct(right);
    }
    if((*d).leftChild != nil)
    {
        Node<keytype, valuetype> *left = (*d).leftChild;
        destruct(left);
    }
    delete(d);
}

template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::~RBTree()
{
    destruct(root);
    if(nil != NULL)
    {
        delete(nil);
    }
}

template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>& RBTree<keytype, valuetype>::operator=(const RBTree &src)
{
    /*if(nil == NULL)
    {
        cout << "A" << endl;
        nil = new Node<keytype, valuetype>;
        (*nil).color = "black";
        (*nil).below = 0;
        if(root == NULL)
        {
            root = nil;
        }
    }*/
    cout << "A" << endl;
    if(root != nil)
    {
        destruct(root);
    }
    cout << "A" << endl;
    siz = src.size();
    root = new Node<keytype, valuetype>(*((*src.root).key()), *((*src.root).value()));
    root -> parent = nil;
    (*root).copy(src.root, src.nil, nil);
}

template <typename keytype, typename valuetype>
RBTree<keytype, valuetype>::RBTree(const RBTree &src)
{
    nil = new Node<keytype, valuetype>;
    (*nil).color = "black";
    (*nil).below = 0;
    siz = src.size();
    root = new Node<keytype, valuetype>(*((*src.root).key()), (*(*src.root).value()));
    root -> parent = nil;
    (*root).copy(src.root, src.nil, nil);
}

template <typename keytype, typename valuetype>
valuetype * RBTree<keytype, valuetype>::search(keytype k)
{
    if(root == nil)
    {
        return NULL;
    }
    Node<keytype, valuetype> *t = (*root).Nsearch(k, nil);
    if(t == nil)
    {
        return NULL;
    }
    else
    {
        return (*t).value();
    }
    
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::iinsert(keytype k, valuetype v)
{
    Node<keytype, valuetype> *z = new Node<keytype, valuetype>(k, v);
    (*z).parent = nil;
    (*z).leftChild = nil;
    (*z).rightChild = nil;
    (*z).below = 1;
    siz++;
    Node<keytype, valuetype> *y = nil;
    Node<keytype, valuetype> *x = root;

    while(x != nil)
    {
        (*x).below = (*x).below + 1;
        y = x;
        if((*(*z).key()) < (*(*x).key()))
        {
            x = (*x).leftChild;
        }
        else
        {
            x = (*x).rightChild;
        }
    }
    (*z).parent = y;
    if(y == nil)
    {
        root = z;
    }
    else if((*(*z).key()) < (*(*y).key()))
    {
        (*y).leftChild = z;
        //(*y).below++;
    }
    else
    {
        (*y).rightChild = z;
        //(*y).below++;
    }
    insertFix(z);
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v)
{
    iinsert(k, v);
}

//replace by predecessor
template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::remove(keytype k)
{
    /*
    Node<keytype, valuetype> *z = (*root).Nsearch(k, nil);
    if(z == nil)
    {
        return 0;
    }
    Node<keytype, valuetype> *y = z;
    Node<keytype, valuetype> *x;
    string oc = (*y).color;
    siz--;
    if((*z).leftChild == nil)
    {
        x = (*z).rightChild;
        transplant(z, (*z).rightChild);
    }
    else if((*z).rightChild == nil)
    {
        x = (*z).leftChild;
        transplant(z, (*z).leftChild);
    }
    else
    {
        y = treeMax((*x).leftChild);
        oc = (*y).color;
        x = (*y).rightChild;
        if((*y).parent == z)
        {
            (*x).parent = y;
        }
        else
        {
            transplant(y, (*y).rightChild);
            (*y).rightChild = (*z).rightChild;
            (*(*y).rightChild).parent = y;
        }
        transplant(z, y);
        (*y).leftChild = (*z).leftChild;
        (*(*y).leftChild).parent = y;
        (*y).color = (*z).color;
    }
    if(oc == "black")
    {
        deleteFixup(x);
    }*/
    Node<keytype, valuetype> *z = (*root).Nsearch(k, nil);
    if(z == nil)
    {
        return 0;
    }
    Node<keytype, valuetype> *y = z;
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *parent;
    string oc = (*y).color;
    siz--;
    if((*z).leftChild == nil)
    {
        //cout << "A" << endl;
        x = (*z).rightChild;
        //belowFix2(x);
        parent = z -> parent;
        belowFix2(z);
        transplant(z, (*z).rightChild);
        if(x != nil)
        {
            parent = x;
        }
        //delete(z);
    }
    else if((*z).rightChild == nil)
    {
        //cout << "A" << endl;
        x = (*z).leftChild;
        //belowFix2(x);
        parent = z -> parent;
        belowFix2(z);
        transplant(z, (*z).leftChild);
        if(x != nil)
        {
            parent = x;
        }
        //delete(z);
    }
    else
    {
        y = treeMax(z);
        //belowFix2(z);
        //cout << *((*y).key()) << endl;
        oc = (*y).color;
        x = (*y).leftChild;
        if((*y).parent == z)
        {
            (*x).parent = y;
            parent = z;
            belowFix2(z);
        }
        else
        {
            parent = y -> parent;
            //belowFix2(x);
            belowFix2(y);
            transplant(y, (*y).leftChild);
            (*y).leftChild = (*z).leftChild;
            (*(*y).leftChild).parent = y;
        }

        transplant(z, y);
        (*y).rightChild = (*z).rightChild;

        (*(*y).rightChild).parent = y;

        (*y).color = (*z).color;

        //cout << *((*y).key()) << endl;

        //delete(z);
        //belowFix(y);
    }
    /*if(x == nil)
    {
        belowFix(parent);
    }
    else
    {
        belowFix(x);
    }*/
    (*nil).below = 0;
    //belowFix2(parent);
    delete(z);

    if(oc == "black")
    {
        //cout << "A" << endl;
        deleteFixup(x);
    }
    return 1;
}

template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rank(keytype k)
{
    return getRank(k);
}

template <typename keytype, typename valuetype>
keytype RBTree<keytype, valuetype>::select(int pos)
{
    //cout << siz << endl;
    //cout << (*root).below << endl;
    return *(*((*root).select(pos, nil))).key();
}

template <typename keytype, typename valuetype>
keytype* RBTree<keytype, valuetype>::successor(keytype k)
{
    if((*root).Nsearch(k, nil) == nil)
    {
        return NULL;
    }
    int r = getRank(k);
    if(r == siz)
    {
        return NULL;
    }
    else
    {
        return (*((*root).select(r + 1, nil))).key();
    }
}

template <typename keytype, typename valuetype>
keytype* RBTree<keytype, valuetype>::predecessor(keytype k)
{
    Node<keytype, valuetype> *x = getPred(k);
    if(x == nil)
    {
        return NULL;
    }
    return (*x).key();
}

template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::size() const
{
    return siz;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::preorder()
{
    if(siz == 0)
    {
        cout << endl;
        return;
    }
    (*root).preorder(nil);
    cout << endl;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::inorder()
{
    if(siz == 0)
    {
        cout << endl;
        return;
    }
    (*root).inorder(nil);
    cout << endl;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::postorder()
{
    if(siz == 0)
    {
        cout << endl;
        return;
    }
    (*root).postorder(nil);
    cout << endl;
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::printk(int k)
{
    int *d = new int;
    *d = 0;
    (*root).printk(k, d, nil);
    cout << endl;
    delete(d);
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::leftRotate(Node<keytype, valuetype> *x)
{
    Node<keytype, valuetype> *y = (*x).rightChild;
    (*x).rightChild = (*y).leftChild;
    if((*y).leftChild != nil)
    {
        (*(*y).leftChild).parent = x;
    }
    (*y).parent = (*x).parent;
    if((*x).parent == nil)
    {
        root = y;
    }
    else if(x == (*(*x).parent).leftChild)
    {
        (*(*x).parent).leftChild = y;
    }
    else
    {
        (*(*x).parent).rightChild = y;
    }
    (*y).leftChild = x;
    (*x).parent = y;
    (*y).below = (*x).below;
    (*x).below = (*(*x).leftChild).below + (*(*x).rightChild).below + 1;
    if((*x).leftChild == nil && (*x).rightChild == nil)
    {
        (*x).below = 1;
    }
    //belowFix((*y).leftChild);
    //belowFix((*y).rightChild);   
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::rightRotate(Node<keytype, valuetype> *x)
{
    Node<keytype, valuetype> *y = (*x).leftChild;
    (*x).leftChild = (*y).rightChild;
    if((*y).rightChild != nil)
    {
        (*(*y).rightChild).parent = x;
    }
    (*y).parent = (*x).parent;
    if((*x).parent == nil)
    {
        root = y;
    }
    else if(x == (*(*x).parent).rightChild)
    {
        (*(*x).parent).rightChild = y;
    }
    else
    {
        (*(*x).parent).leftChild = y;
    }
    (*y).rightChild = x;
    (*x).parent = y;  
    
    (*y).below = (*x).below;
    (*x).below = (*(*x).leftChild).below + (*(*x).rightChild).below + 1;
    if((*x).leftChild == nil && (*x).rightChild == nil)
    {
        (*x).below = 1;
    }
    //belowFix((*y).leftChild);
    //belowFix((*y).rightChild);  
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::insertFix(Node<keytype, valuetype> *z)
{
    while((*(*z).parent).color == "red")
    {
        if((*z).parent == (*(*(*z).parent).parent).leftChild)
        {
            Node<keytype, valuetype>* y = (*(*(*z).parent).parent).rightChild;
            if((*y).color == "red")
            {
                (*(*z).parent).color = "black";
                (*y).color = "black";
                (*(*(*z).parent).parent).color = "red";
                z = (*(*z).parent).parent;
                //belowFix(z);
            }
            else
            {
                if(z == (*(*z).parent).rightChild)
                {
                    z = (*z).parent;
                    leftRotate(z);
                }
                (*(*z).parent).color = "black";
                (*(*(*z).parent).parent).color = "red";
                rightRotate((*(*z).parent).parent);
            }
        }
        else
        {
            Node<keytype, valuetype>* y = (*(*(*z).parent).parent).leftChild;
            if((*y).color == "red")
            {
                (*(*z).parent).color = "black";
                (*y).color = "black";
                (*(*(*z).parent).parent).color = "red";
                z = (*(*z).parent).parent;
                //belowFix(z);
            }
            else
            {
                if(z == (*(*z).parent).leftChild)
                {
                    z = (*z).parent;
                    rightRotate(z);
                }
                (*(*z).parent).color = "black";
                (*(*(*z).parent).parent).color = "red";
                leftRotate((*(*z).parent).parent);
            }
        }
    }
    (*root).color = "black";
    (*nil).color = "black";
}

/*
template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::checker(Node<keytype, valuetype>* n, int bc, int* array, int* t, int* c, keytype* b, int* s)
{
    if(n == nil)
    {
        *c = 0;
        return;
    }
    keytype k = *((*n).key());
    if(n -> leftChild == nil && n -> rightChild == nil)
    {
        //cout << "Leaf: " << k << " " << n -> below << endl;
    }

    if((*n).parent != nil)
    {
        if((*(*n).parent).color == "red" && (*n).color == "red")
        {
            *c = 0;
            cout << "RED" << endl;
        }
    }
    
    if((*n).color == "black")
    {
        bc++;
    }
    if((*n).leftChild != nil)
    {
        Node<keytype, valuetype> * e = (*n).leftChild;
        if(e -> parent != n)
        {
            cout << "A" << endl;
        }
    }
    
    if((*n).rightChild != nil)
    {
        Node<keytype, valuetype> * e = (*n).rightChild;
        if(e -> parent != n)
        {
            cout << "B" << endl;
        }
    }
    if(n -> below != (1 + (*n).rightChild -> below + (*n).leftChild -> below))
    {
        // *c = 0;
        *c = 1;
    }
    keytype kl = *(((*(*n).leftChild)).key());
    keytype kr = *(((*(*n).rightChild)).key());
    if(k > kr)
    {
        if(n -> rightChild != nil)
        {
            cout << "Right issue with " << k << endl;
            *c = 0;
        }
    }
    if(k < kl)
    {
        if(n -> leftChild != nil)
        {
            cout << "Left issue with " << k << endl;
            *c = 0;
        }
    }
    //(*s)++;
    if((*n).leftChild !=  nil)
    {
        checker((*n).leftChild, bc, array, t, c, b, s);
    }

    //b[*s] = *(*n).key();
    // *s = *s + 1;
    if((*n).rightChild !=  nil)
    {
        checker((*n).rightChild, bc, array, t, c, b, s);
    }
    if((*n).leftChild == nil && (*n).rightChild == nil)
    {
        array[*t] = bc;
        (*t)++;
    }
}

template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::test()
{
    cout << "Root size: " << (*root).below << " Tree Size: " << siz << endl;
    cout << (*nil).below << endl;
    if(nil -> parent == NULL)
    {
        //cout << "GOOD" << endl;
    }
    int * a;
    keytype * b;
    b = new keytype[siz];
    a = new int[siz];
    int bc = 0;
    int* t = new int;
    *t = 0;
    int *s = new int;
    *s = 0;
    
    int *c = new int;

    *c = 1;
    checker(root, bc, a, t, c, b, s);

    //cout << *s << endl;
    (*root).inorder2(b, s, nil);    
    //cout << siz << endl;
    //cout << *s << endl;
    cout << "Difference in size: " << siz - *s << endl;
    if(root != nil && (*root).color != "black")
    {
        *c = 0;
    }

    for(int i = 1; i < *t; i++)
    {
        if(a[i] != a[i-1])
        {
            cout << "BLACK" << endl;
            *c = 0;
            cout << i << endl;
            cout << a[i] - a[i-1] << endl;
            //break;
        }
    }

    for(int i = 1; i < siz; i++)
    {
        if(b[i] < b[i - 1])
        {
            cout << i << " " << b[i] << endl;
            //cout << i - 1 << " " << b[i-1] << endl;
            cout << "INORDER" << endl;
            *c = 0;
            break;
        }
    }

    if(*c == 0)
    {
        cout << "It did not work." << endl;
        return 0;
    }
    else 
    {
        cout << "It worked." << endl;
        return 1;
    }

    delete[](a);
    delete(t);
    delete(c);
    delete(s);
    delete[](b);
}*/

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::transplant(Node<keytype, valuetype>* u, Node<keytype, valuetype>* v)
{
    if((*u).parent == nil)
    {
        root = v;
    }
    else if((*(*u).parent).leftChild == u)
    {
        (*(*u).parent).leftChild = v;
    }
    else
    {
        (*(*u).parent).rightChild = v;
    }
    (*v).parent = (*u).parent;
    (*v).below = (*u).below;
    (*nil).below = 0;
    //possibly not necessary 
    //belowFix(u);
    //belowFix(v);
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::deleteFixup(Node<keytype, valuetype>* x)
{
    while(x != root && (*x).color == "black")
    {
        if(x == (*(*x).parent).leftChild)
        {
            Node<keytype, valuetype> *w = (*(*x).parent).rightChild;
            if((*w).color == "red")
            {
                (*w).color = "black";
                (*(*x).parent).color = "red";
                leftRotate((*x).parent);
                w = (*(*x).parent).rightChild;
            }
            if((*(*w).leftChild).color == "black" && (*(*w).rightChild).color == "black")
            {
                (*w).color = "red";
                x = (*x).parent;
            }
            else
            {
                if((*(*w).rightChild).color == "black")
                {
                    (*(*w).leftChild).color = "black";
                    (*w).color = "red";
                    rightRotate(w);
                    w = (*(*x).parent).rightChild;
                }
                (*w).color = (*(*x).parent).color;
                (*(*x).parent).color = "black";
                (*(*w).rightChild).color = "black";
                leftRotate((*x).parent);
                x = root;
            }
        }
        else
        {
            Node<keytype, valuetype> *w = (*(*x).parent).leftChild;
            if((*w).color == "red")
            {
                (*w).color = "black";
                (*(*x).parent).color = "red";
                rightRotate((*x).parent);
                w = (*(*x).parent).leftChild;
            }
            if((*(*w).leftChild).color == "black" && (*(*w).rightChild).color == "black")
            {
                (*w).color = "red";
                x = (*x).parent;
            }
            else
            {
                if((*(*w).leftChild).color == "black")
                {
                    (*(*w).rightChild).color = "black";
                    (*w).color = "red";
                    leftRotate(w);
                    w =(*(*x).parent).leftChild;
                }
                (*w).color = (*(*x).parent).color;
                (*(*x).parent).color = "black";
                (*(*w).leftChild).color = "black";
                rightRotate((*x).parent);
                x = root;
            }
        }
    }
    (*x).color = "black";
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::belowFix(Node<keytype, valuetype> *n)
{
    if(n == nil)
    {
        return;
    }
    (*n).below = 1;
    if((*n).rightChild != nil)
    {
        (*n).below += (1 + (*(*n).rightChild).below);
    }
    if((*n).leftChild != nil)
    {
        (*n).below += (1 + (*(*n).leftChild).below);
    }
    if(n -> parent != nil)
    {
        belowFix(n -> parent);
    }
}

template <typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::belowFix2(Node<keytype, valuetype> *n)
{
    Node<keytype, valuetype>* w = n;
    while(w != nil)
    {
        (*w).below -= 1;
        w = w -> parent;
    }
}

template <typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::getRank(keytype k)
{
    Node<keytype, valuetype> *x = (*root).Nsearch(k, nil);
    if(x == nil)
    {
        return 0;
    }
    return (*x).findRank(k, nil);
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* RBTree<keytype, valuetype>::getPred(keytype k)
{
    if((*root).Nsearch(k, nil) == nil)
    {
        return nil;
    }
    int r = getRank(k);
    if(r == 1)
    {
        return nil;
    }
    else
    {
        return (*root).select(r - 1, nil);
    }
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* RBTree<keytype, valuetype>::treeMax(Node<keytype, valuetype>* n)
{
    n = (*n).leftChild;

    while((*n).rightChild != nil)
    {
        n = (*n).rightChild;
    }
    return n;
}