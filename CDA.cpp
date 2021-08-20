#include <time.h>
#include <stdlib.h>

using namespace std;

template <typename elmtype>
class CDA
{
    private:
        elmtype *a;
        int frontIndex;
        int reverseFlag;
        int size;
        int capacity;
        elmtype* outOfBounds;
    public:
        CDA();
        CDA(int s);
        ~CDA();
        CDA &operator=(const CDA &src); 
        CDA(const CDA &src);     
        elmtype& operator[](int i) const;
        void AddEnd(elmtype v);
        void AddFront(elmtype v);
        void DelEnd();
        void DelFront();
        int Length() const; 
        int Capacity() const; 
        void Clear();
        void Reverse();
        elmtype Select(int k);
        void Sort();
        int Search(elmtype e) const;
        int BinSearch(elmtype e) const;
};

template <typename elmtype>
CDA<elmtype>::CDA()
{
    size = 0;
    capacity = 1;
    reverseFlag = 1;
    frontIndex = capacity;
    a = new elmtype[capacity];
    outOfBounds = new elmtype;
}

template <typename elmtype>
CDA<elmtype>::CDA(int s)
{
    size = s;
    capacity = s;
    reverseFlag = 1;
    frontIndex = capacity;
    a = new elmtype[capacity];
    outOfBounds = new elmtype;
}

template <typename elmtype>
int CDA<elmtype>::Length() const
{
    return size;
}

template <typename elmtype>
int CDA<elmtype>::Capacity() const
{
    return capacity;
}

template <typename elmtype>
CDA<elmtype>::~CDA()
{
    if(a != NULL)
    {
        delete[](a);
    }
    if(outOfBounds != NULL)
    {
        delete(outOfBounds);
    }
}

template <typename elmtype>
elmtype& CDA<elmtype>::operator[](int i) const
{
    if(i < 0 || i >= size)
    {
        return *outOfBounds;
    }

    i *= reverseFlag;
    
    return a[((frontIndex + i) % capacity)];
}

template <typename elmtype>
CDA<elmtype> &CDA<elmtype>::operator=(const CDA &src)
{
    /*if(src == NULL)
    {
        return;
    }
    if(a != NULL)
    {
        delete(a);
    }*/

    size = src.Length();
    capacity = src.Capacity();
    outOfBounds = new elmtype;

    a = new elmtype[capacity];
    reverseFlag = 1;
    frontIndex = capacity;

    for(int i = 0; i < size; i++)
    {
        a[i] = src[i];
    }
    return *this;
}

template <typename elmtype>
CDA<elmtype>::CDA(const CDA &src)
{
    /*if(src == NULL)
    {
        return;
    }
    if(a != NULL)
    {
        delete(a);
    }*/
    size = src.Length();
    capacity = src.Capacity();
    outOfBounds = new elmtype;
    a = new elmtype[capacity];
    reverseFlag = 1;
    frontIndex = capacity;

    for(int i = 0; i < size; i++)
    {
        a[i] = src[i];
    }

}

template <typename elmtype>
void CDA<elmtype>::AddEnd(elmtype v)
{
    if(size == capacity)
    {
        capacity *= 2;
        elmtype* d = new elmtype[capacity];
        for(int i = 0; i < size; i++)
        {
            int currIndex = frontIndex + (i * reverseFlag);
            d[i] = a[currIndex % size];
        }
        frontIndex = capacity;
        d[size] = v;
        delete[](a);
        a = d;
        size++;
        reverseFlag = 1;
        return;
    }

    a[(frontIndex + (size * reverseFlag)) % capacity] = v;
    size++;
    return;
}

template <typename elmtype>
void CDA<elmtype>::AddFront(elmtype v)
{
    if(size == capacity)
    {
        capacity *= 2;
        elmtype* d = new elmtype[capacity];
        for(int i = 0; i < size; i++)
        {
            int curIndex = frontIndex + (i * reverseFlag);
            d[i + 1] = a[curIndex % size];
        }
        d[0] = v;
        size++;
        delete[](a);
        frontIndex = capacity;
        a = d;
        reverseFlag = 1;
        return; 
    }

    frontIndex -= reverseFlag;
    a[frontIndex % capacity] = v;
    size++;
    return;
}

template <typename elmtype>
void CDA<elmtype>::DelEnd()
{
    size--;

    if(capacity / 2 < 4)
    {
        return;
    }

    if(size * 4 <= capacity)
    {
        elmtype* d = new elmtype[capacity / 2];
        for(int i = 0; i < size; i++)
        {
            d[i] = a[(frontIndex + (i * reverseFlag)) % capacity];
        }   
        capacity /= 2;
        frontIndex = capacity;
        delete[](a);
        a = d;
        reverseFlag = 1;
    }
    return;
}

template <typename elmtype>
void CDA<elmtype>::DelFront()
{
    frontIndex += reverseFlag;
    size--;

    if(capacity / 2 < 4)
    {
        return;
    }

    if(size * 4 <= capacity)
    {
        elmtype* d = new elmtype[capacity / 2];
        for(int i = 0; i < size; i++)
        {
            d[i] = a[(frontIndex + (i * reverseFlag)) % capacity];
        }   
        capacity /= 2;
        frontIndex = capacity;
        delete[](a);
        a = d;
        reverseFlag = 1;
    }
    return;
}

template <typename elmtype>
void CDA<elmtype>::Clear()
{
    if(a != NULL)
    {
        delete[](a);
    }
    capacity = 4;
    size = 0;
    a = new elmtype[capacity];
    reverseFlag = 1;
    frontIndex = capacity;
    return;
}

template <typename elmtype>
void CDA<elmtype>::Reverse()
{
    frontIndex = frontIndex + ((size -1) * reverseFlag);
    reverseFlag *= -1;
    return;
}

template <typename elmtype>
elmtype CDA<elmtype>::Select(int k)
{
    int ran;

    srand(time(NULL));

    ran = rand() % size;

    elmtype pivot = a[(frontIndex + (reverseFlag * ran)) % capacity];

    CDA L;
    CDA E;
    CDA G;
    for(int i = 0; i < size; i++)
    {
        elmtype x = a[(frontIndex + (reverseFlag * i)) % capacity];
        if (x < pivot)
        {
            L.AddEnd(x);
        }
        else if (x == pivot)
        {
            E.AddEnd(x);
        }
        else
        {
            G.AddEnd(x);
        }
        
    }
    if (k <= L.size)
    {
        return L.Select(k);
    }
    else if (k <= L.size + E.size) 
    {
        return pivot;
    }
    else 
    {
        return G.Select(k - L.Length() - E.Length());
    }
}

template <typename elmtype>
void quickSort(elmtype* a, int d, int k)
{
    if(d >= k)
    {
        return;
    }
    int j;
    int h = k;
    int l = d;
    elmtype pivot = a[(d + k) / 2];
    int b = 1;
    while(b)
    {
        while(a[l] < pivot)
        {
            l++;
        }
        while(a[h] > pivot)
        {
            h--;
        }
        if(l >= h)
        {
            b = 0;
        }
        else
        {
            elmtype temp = a[l];
            a[l] = a[h];
            a[h] = temp;
            l++;
            h--;
        }   
    }
    j = h;
    quickSort(a, d, j);
    quickSort(a, j + 1, k);
}

template <typename elmtype>
void CDA<elmtype>::Sort()
{
    elmtype* f = new elmtype[size];

    for(int i = 0; i < size; i++)
    {
        f[i] = a[(frontIndex + (reverseFlag * i)) % capacity];
    }

    frontIndex = capacity;
    reverseFlag = 1;

    quickSort(f, 0, size - 1);

    for(int i = 0; i < size; i++)
    {
        a[i] = f[i];
    }

    return;
}

template <typename elmtype>
int CDA<elmtype>::Search(elmtype e) const
{
    int index = -1;

    for(int i = 0; i < size; i++)
    {
        elmtype curr = a[(frontIndex + (reverseFlag * i)) % capacity];
        
        if(curr == e)
        {
            index = i;
            break;
        }
    }
    return index;
    
}

template <typename elmtype>
int bSearch(elmtype* a, int frontIndex, int reverseFlag, elmtype e, int size, int capacity, int l, int h, int pI, elmtype p, int f)
{
    if(f > size)
    {
        return -1;
    }
    if(l < 0 || h < 0)
    {
        pI = 0;
        return ~pI;
    }
    int mid = (l + h) / 2;
    elmtype midE = a[(frontIndex + (mid * reverseFlag)) % capacity];
    if(midE == e)
    {
        return mid;
    }
    if(midE < p)
    {
        if(midE > e)
        {
            p = midE;
            pI = mid;
        } 
    }
    if(h == l || h < l)
    {
        return ~pI;
    }
    if(e > midE)
    {
        return bSearch(a, frontIndex, reverseFlag, e, size, capacity, mid + 1, h, pI, p, f + 1);
    }
    else
    {
        return bSearch(a, frontIndex, reverseFlag, e, size, capacity, l, mid - 1, pI, p, f + 1);
    }
}

template <typename elmtype>
int CDA<elmtype>::BinSearch(elmtype e) const
{
    elmtype high = a[(frontIndex + ((size - 1) * reverseFlag)) % capacity];
    if(e > high)
    {
        return ~size;
    }
    return bSearch(a, frontIndex, reverseFlag, e, size, capacity, 0, size - 1, size - 1, high, 0);
}