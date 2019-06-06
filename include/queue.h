#ifndef QUEUE_CLASS
#define QUEUE_CLASS

#include <iostream.h>
#include <stdlib.h>

#include "link.h"

template <class T>
class Queue
{
    private:
    	// a linked list object to hold the queue items
        LinkedList<T> queueList;
        
    public:
    	// constructor
        Queue(void);
        
        // queue access methods 
        void QInsert(const T& elt);
        T QDelete(void);
        
        // queue access
        T QFront(void);
        
        // queue test methods
        int QLength(void) const;
        int QEmpty(void) const;
        void QClear(void);
};

// constructor
template <class T>
Queue<T>::Queue(void)
{}

// LinkedList method ListSize returns length of list
template <class T>
int Queue<T>::QLength(void) const
{
    return queueList.ListSize();
}

// LinkedList method ListEmpty tests for empty queue
template <class T>
int Queue<T>::QEmpty(void) const
{
    return queueList.ListEmpty();
}

// LinkedList method ClearList clears the queue
template <class T>
void Queue<T>::QClear(void)
{
    queueList.ClearList();
}

// LinkedList method InsertRear inserts item at rear
template <class T>
void Queue<T>::QInsert(const T& elt)
{
    queueList.InsertRear(elt);
}

// LinkedList method DeleteFront removes item from front
template <class T>
T Queue<T>::QDelete(void)
{
	// test for an empty queue and terminate if true
    if (queueList.ListEmpty())
    {
        cerr << "Calling QDelete for an empty queue!" << endl;
        exit(1);
    }
    return queueList.DeleteFront();
}

// return the data value from the first item in the queue
template <class T>
T Queue<T>::QFront(void)
{
	// test for an empty queue and terminate if true
    if (queueList.ListEmpty())
    {
        cerr << "Calling QFront for an empty queue!" << endl;
        exit(1);
    }
    
    // reset to front of the queue and return data
    queueList.Reset();
    return queueList.Data();
}

#endif  // QUEUE_CLASS
