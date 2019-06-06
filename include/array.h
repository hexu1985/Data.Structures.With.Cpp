#ifndef ARRAY_CLASS
#define ARRAY_CLASS

#include <iostream.h>
#include <stdlib.h>

#ifndef NULL
const int NULL = 0;
#endif  // NULL

enum ErrorType
  {invalidArraySize, memoryAllocationError, indexOutOfRange};

char *errorMsg[] =
{
    "Invalid array size", "Memory allocation error",
    "Invalid index: "
};

template <class T> 
class Array
{
    private:
        // a dynamically allocated list containing size items
        T*  alist;
        int size;

        // error handling method
        void Error(ErrorType error,int badIndex=0) const;

    public:
        // constructors and destructor
        Array(int sz = 50);                         
        Array(const Array<T>& A);   
        ~Array(void);

        // assignment, indexing and pointer conversion
        Array<T>& operator= (const Array<T>& rhs);
        T& operator[](int i);
        operator T* (void) const;

        // size operations
        int ListSize(void) const;   // read the size
        void Resize(int sz);        // modify the size
};

// prints the message corresponding to error
template <class T>
void Array<T>::Error(ErrorType error, int badIndex) const
{
    cerr << errorMsg[error];
    // for indexOutOfRange, print the bad index
    if (error == indexOutOfRange)
        cerr << badIndex;
    cerr << endl;
    exit(1);
}

// constructor
template <class T>
Array<T>::Array(int sz)
{
    // check for an invalid size parameter  
    if (sz <= 0) 
        Error(invalidArraySize);
    // assign the size and dynamically allocate memory
    size = sz;
    alist = new T[size];    
    // make sure that system allocates the desired memory, 
    if (alist == NULL)
        Error(memoryAllocationError);
}

// destructor
template <class T>
Array<T>::~Array(void)
{ 
    delete [] alist;
}

// copy constructor
template <class T>
Array<T>::Array(const Array<T>& X)
{
    // get size from object X and assign to current object 
    int n = X.size;

    size = n;

    // allocate new memory for object and do error checking
    alist = new T[n];           // allocate dynamic array
    if (alist == NULL)
        Error(memoryAllocationError);
    
    // copy array items from x to current object  
    T* srcptr = X.alist;    // address at start of X.alist
    T* destptr = alist;     // address at start of alist
    while (n--)             // copy list
        *destptr++ = *srcptr++;
}

// assignment operator. assign rhs to the current object
template <class T>
Array<T>& Array<T>::operator= (const Array<T>& rhs)
{
    // record the size of rhs
    int n = rhs.size;

    // if sizes not the same, delete memory and reallocate
    if (size != n)
    {
        delete [] alist;        // destroy original memory
        alist = new T[n];       // allocate a new array
        if (alist == NULL)
            Error(memoryAllocationError);
        size = n;
    }
 
    // copy array items from rhs to current object
   T* destptr = alist;
   T* srcptr = rhs.alist;
    while (n--) 
        *destptr++ = *srcptr++;

    // return reference to the current object
    return *this;
}

// overloaded index operator
template <class T>
T& Array<T>::operator[] (int n)
{
   // do array bounds checking
   if (n < 0 || n > size-1)
      Error(indexOutOfRange,n);
   // return the element from the private array list
   return alist[n];
}

// pointer conversion operator
template <class T>
Array<T>::operator T* (void) const
{
    // return address of private array in the current object
    return alist;
}

template <class T>
int Array<T>::ListSize(void) const
{
    return size;
}

// resize operator
template <class T>
void Array<T>::Resize(int sz)
{
    // test new size parameter; terminate if size <= 0
    if (sz <= 0) 
        Error(invalidArraySize);
    // nothing to do if size hasn't changed
    if (sz == size)
        return;

    // request new memory and verify system response
    T* newlist = new T[sz];
    if (newlist == NULL)
        Error(memoryAllocationError);

    // declare n with value sz (truncating list)
    // or otherwise declare n to be the current size
    int n = (sz <= size) ? sz : size;

    // copy n array items from old to new memory
    T* srcptr = alist;      // address at start of alist
    T* destptr = newlist;   // address at start of newlist
    while (n--)             // copy list
        *destptr++ = *srcptr++;
    
    // delete old list
    delete[] alist;

    // reset alist to point at newlist and update the size
    alist = newlist;
    size = sz;
}

#endif  // ARRAY_CLASS
