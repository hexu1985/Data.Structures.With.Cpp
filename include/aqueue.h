#ifndef QUEUE_CLASS
#define QUEUE_CLASS

#include <iostream.h>
#include <stdlib.h>

// maximum size of a queue list
const int MaxQSize = 50;

class Queue
{
    private:
        // queue array and its parameters
        int front, rear, count;
        DataType qlist[MaxQSize];

    public:
        // constructor
        Queue (void);       // initialize integer data members
        
        // queue modification operations
        void QInsert(const DataType& item);
        DataType QDelete(void);
        void ClearQueue(void);
        
        // queue access
        DataType QFront(void) const;
        
        // queue test methods
        int QLength(void) const;
        int QEmpty(void) const;
        int QFull(void) const;
};
                                  
// initialize queue front, rear, count
Queue::Queue (void) : front(0), rear(0), count(0)
{}

// insert item into the queue 
void Queue::QInsert (const DataType& item)
{
    // terminate if queue is full
    if (count == MaxQSize)
    {
        cerr << "Queue overflow!" << endl;
        exit(1);
    }
    // increment count, assign item to qlist and update rear
    count++;
    qlist[rear] = item;
    rear = (rear+1) % MaxQSize;
}

// delete element from front of queue and return its value
DataType Queue::QDelete(void)
{
    DataType temp;

    // if qlist is empty, terminate the program
    if (count == 0)
    {
        cerr << "Deleting from an empty queue!" << endl;
        exit(1);
    }
    
    // record value at the front of the queue
    temp = qlist[front];

    // decrement count, advance front and return former front
    count--;
    front = (front+1) % MaxQSize;
    return temp;
}

// return value of the first entry 
DataType Queue::QFront(void) const
{
    return qlist[front];
}
  
// return number of queue elements
int Queue::QLength(void) const
{
    return count;
}

// test for an empty queue
int Queue::QEmpty(void) const
{
    // return the logical value count == 0
    return count == 0;
}

// test for a full queue
int Queue::QFull(void) const
{
    // return the logical value count == MaxQSize
    return count == MaxQSize;
}

// clear the queue by resetting count, front and rear to 0
void Queue::ClearQueue(void) 
{
    count = 0;
    front = 0; 
    rear = 0; 
}
    
#endif  // QUEUE_CLASS
  
