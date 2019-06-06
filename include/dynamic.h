#ifndef DYNAMIC_DEMO_CLASS
#define DYNAMIC_DEMO_CLASS

#include <iostream.h>

template <class T>
class DynamicClass
{
    private:
        // variable of type T and a pointer to data of type T
        T member1;
        T *member2;
    public:
        // constructors
        DynamicClass(const T& m1, const T& m2);
        DynamicClass(const DynamicClass<T>& obj);
        
        // destructor
        ~DynamicClass(void);

        // assignment operator
        DynamicClass<T>& operator= (const DynamicClass<T>& rhs);
};

// constructor with parameters to initialize member data
template <class T>
DynamicClass<T>::DynamicClass(const T& m1, const T& m2)
{
    // parameter m1 initializes static member
    member1 = m1;
    // allocate dynamic memory. initialize it with value m2
    member2 = new T(m2);
    cout << "Constructor: " << member1 << '/'
         << *member2 << endl;
}

// copy constructor. initialize mew object to have the
// same data as obj.
template <class T>
DynamicClass<T>::DynamicClass(const DynamicClass<T>& obj)
{
    // copy static data member from obj to current object
    member1 = obj.member1;              
    // allocate dynamic memory and initialize it with
    // value *obj.member2.
    member2 = new T(*obj.member2); 
    cout << "Copy Constructor:  " << member1
         << '/' << *member2 << endl;
}

// destructor. deallocates dynamic memory allocated
// by the constructor
template <class T>
DynamicClass<T>::~DynamicClass(void)
{
    cout << "Destructor: " << member1 << '/'
         << *member2 << endl;
    delete member2;                 
}

// overloaded assignment operator. returns a reference to 
// current object
template <class T>
DynamicClass<T>& DynamicClass<T>::operator=
               (const DynamicClass<T>& rhs)
{
    // copy static data member from rhs to the current object
    member1 = rhs.member1;
    // contents of dynamic memory must be same as that of rhs
    *member2 = *rhs.member2;        
    cout << "Assignment Operator: "<< member1 << '/'
         << *member2 << endl;
    return *this;                   
}

#endif  // DYNAMIC_DEMO_CLASS
