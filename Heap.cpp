#include "CDA.cpp"
#include <iostream>
using namespace std;

template<typename keytype>
class Heap
{
    private:
        CDA<keytype> array;
        keytype at(int index);
        void set(int index, keytype k);
        void sinkDown(int index);
    public:
        Heap();
        Heap(keytype k[], int s);
        Heap &operator=(const Heap &src); 
        Heap(const Heap &src);  
        ~Heap();
        keytype peekKey();
        keytype extractMin();
        void insert(keytype k); 
        void printKey();
        //void test();
};

template<typename keytype>
Heap<keytype>::Heap()
{
    //
}

template<typename keytype>
Heap<keytype>::Heap(keytype k[], int s)
{
    for(int i = 0; i < s; i++)
    {
        array.AddEnd(k[i]);
    }
    for(int i = array.Length() / 2; i > 0; i--)
    {
        keytype parent = at(i);
        keytype lowestChild = at(i * 2);
        int lowestIndex = i * 2;
        if((i * 2) + 1 <= array.Length())
        {
            if(at((i * 2) + 1) < lowestChild)
            {
                lowestChild = at((i * 2) + 1);
                lowestIndex++;
            }
        }
        if(lowestChild < at(i))
        {
            set(lowestIndex, at(i));
            set(i, lowestChild);
            sinkDown(lowestIndex);
        }
    }
}

template<typename keytype>
Heap<keytype> &Heap<keytype>::operator=(const Heap &src)
{
    array.Clear();
    for(int i = 0; i < src.array.Length(); i++)
    {
        array.AddEnd(src.array[i]);
    }
    return (*this);
}

template<typename keytype>
Heap<keytype>::Heap(const Heap &src)
{
    for(int i = 0; i < src.array.Length(); i++)
    {
        array.AddEnd(src.array[i]);
    }
}

template<typename keytype>
Heap<keytype>::~Heap()
{
    //
}

template<typename keytype>
keytype Heap<keytype>::peekKey()
{
    return at(1);
}

template<typename keytype>
keytype Heap<keytype>::extractMin()
{
    keytype returnValue = at(1);

    keytype temp = at(array.Length());
    set(array.Length(), at(1));
    set(1, temp);
    array.DelEnd();

    sinkDown(1);

    return returnValue;
}

template<typename keytype>
void Heap<keytype>::insert(keytype k)
{
    array.AddEnd(k);
    int currIndex = array.Length();

    while(currIndex > 1 && at(currIndex) < at(currIndex / 2))
    {
        keytype temp = at(currIndex);
        set(currIndex, at(currIndex / 2));
        set(currIndex / 2, temp);
        currIndex /= 2;
    }
}

template<typename keytype>
void Heap<keytype>::printKey()
{
    for(int i = 0; i < array.Length(); i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

template<typename keytype>
keytype Heap<keytype>::at(int index)
{
    return array[index - 1];
}

template<typename keytype>
void Heap<keytype>::set(int index, keytype k)
{
    array[index - 1] = k;
}

template<typename keytype>
void Heap<keytype>::sinkDown(int index)
{
    while(1)
    {
        int i = index;
        if(index > array.Length() / 2)
        {
            break;
        }
        if(at(index) <= at(index * 2))
        {
            if((index * 2) + 1 < array.Length())
            {
                if(at(index) <= at((index * 2) + 1))
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        keytype parent = at(i);
        keytype lowestChild = at(i * 2);
        int lowestIndex = i * 2;
        if((i * 2) + 1 <= array.Length())
        {
            if(at((i * 2) + 1) < lowestChild)
            {
                lowestChild = at((i * 2) + 1);
                lowestIndex++;
            }
        }
        if(lowestChild < at(i))
        {
            set(lowestIndex, at(i));
            set(i, lowestChild);
            index = lowestIndex;
        }
    }
}

/*
template<typename keytype>
void Heap<keytype>::test()
{
    int d = 1;
    for(int i = 2; i < array.Length(); i++)
    {
        if(at(i) < at(i / 2))
        {
            d = 0;
        }
    }

    if(d == 1)
    {
        cout << "It worked." << endl;
    }
    else
    {
        cout << "It did not work." << endl;
    }
}
*/