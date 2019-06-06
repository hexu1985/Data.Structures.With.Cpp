#ifndef STACK_CLASS
#define STACK_CLASS

#include <iostream.h>
#include <stdlib.h>

#include "link.h"

template <class T>
class Stack
{
    private:
    	// a linked list object to hold the stack items
    	LinkedList<T> stackList;

	public:
    	// constructor
		Stack(void);
		
        // stack access methods
        void Push(const T& item);
        T Pop(void);
        T Peek(void);
        
        // stack test and clear methods
        int StackEmpty(void) const;
        void ClearStack(void);
};

// constructor
template <class T>
Stack<T>::Stack(void)
{}

// uses the LinkedList method ClearList to clear the stack
template <class T>
void Stack<T>::ClearStack(void)
{
    stackList.ClearList();
}
 
// use the LinkedList method InsertFront to push item
template <class T>
void Stack<T>::Push(const T& item)
{
	stackList.InsertFront(item);
}

// use the LinkedList method DeleteFront to pop stack
template <class T>
T Stack<T>::Pop(void)
{
	// check for an empty linked list
	if (stackList.ListEmpty())
	{
		cerr << "Popping an empty stack" << endl;
		exit(1);
	}
	// delete first node and return its data value
	return stackList.DeleteFront();
}

// returns the data value of the first first item on the stack
template <class T>
T Stack<T>::Peek(void)
{
	// check for an empty linked list
    if (stackList.ListEmpty())
    {
        cerr << "Calling Peek for an empty stack" << endl;
        exit(1);
    }
    // reset to the front of linked list and return value
    stackList.Reset();
    return stackList.Data();
}

// use the LinkedList method ListEmpty to test for empty stack
template <class T>
int Stack<T>::StackEmpty(void) const
{
    return stackList.ListEmpty();
}

#endif  // STACK_CLASS