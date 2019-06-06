#ifndef ABSTRACT_LIST_BASE_CLASS
#define ABSTRACT_LIST_BASE_CLASS

template <class T>
class List
{
    protected:
        // number of elements in the list. updated by derived class
        int size;
    public:
        // constructor
        List(void);

        // add a virtual destructor in case a derived class
        // uses dynamic memory
        virtual ~List(void);
        
        // list access methods
        virtual int ListSize(void) const;                             
        virtual int ListEmpty(void) const;
        virtual int Find (T& item) = 0;
        
        // list modification methods
        virtual void Insert(const T& item) = 0;
        virtual void Delete(const T& item) = 0;
        virtual void ClearList(void) = 0;   
};

// constructor sets size to 0
template <class T>
List<T>::List(void): size(0)
{}

// the virtual destructor does nothing
template <class T>
List<T>::~List(void)
{}

// return the list size
template <class T>
int List<T>::ListSize(void) const
{
    return size;
}
                                
// test for an empty list
template <class T>
int List<T>::ListEmpty(void) const
{
    return size == 0;
}

#endif // ABSTRACT_LIST_BASE_CLASS
