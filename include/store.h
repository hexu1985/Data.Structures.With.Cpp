#ifndef TEMPLATE_STORE_CLASS
#define TEMPLATE_STORE_CLASS

#include <iostream.h>
#include <stdlib.h>

template <class T>
class Store
{
    private:
        T item;         // object holds a data value
        int haveValue;  // flag set when item is initialized
    
    public:
        // constructor (default)
        Store(void);
        
        // data retrieval and storage operations
        T GetElement(void);
        void PutElement(T x); 
};

// declare that the data value is not initialized
template <class T>                              
Store<T>::Store(void): haveValue(0)
{}


// retrieve item if initialized
template <class T>                 
T Store<T>::GetElement(void)    
{
    // terminate if client tries to access uninitialized data
    if (haveValue == 0)
    {
        cerr << "No item present!" << endl;
        exit(1);
    }
    return item;    // returns item from storage 
}

// put item in storage 
template <class T>                              
void Store<T>::PutElement(T x)
{
    haveValue++;                        // haveValue is TRUE
    item = x;                           // store x
}

#endif  // TEMPLATE_STORE_CLASS


