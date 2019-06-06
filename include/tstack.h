#ifndef TEMPLATE_STACK_CLASS
#define TEMPLATE_STACK_CLASS

#include <iostream.h>
#include <stdlib.h>

const int MaxStackSize = 50;

template <class T>
class Stack
{
    private:
        // private data members. stack array and top
        T stacklist[MaxStackSize];
        int top;
    public:
        // constructor
        Stack (void);     // initialize top
        
        // stack modification operations
        void Push (const T& item);
        T Pop (void);
        void ClearStack(void);
        
        // stack access
        T Peek (void) const;
        
        // stack test methods
        int StackEmpty(void) const;
        int StackFull(void) const;
};

// initialize stack top
template <class T>
Stack<T>::Stack (void): top(-1)
{}

// push item on the the stack
template <class T>
void Stack<T>::Push (const T& item)
{
    // if all elements of stacklist used, terminate program
    if (top == MaxStackSize-1)
    {
        cerr << "Stack overflow!" << endl;
        exit(1);
    }
    
    // increment top and copy item to stacklist
    top++;
    stacklist[top] = item;
}

// pop the stack and return the top element
template <class T>
T Stack<T>::Pop (void)
{
    T temp;

    // if stack is empty, terminate the program
    if (top == -1)
    {
        cerr << "Attempt to pop an empty stack!" << endl;
        exit(1);
    }
    
    // record the top element
    temp = stacklist[top];
    
    // decrement top and return former top element
    top--;
    return temp;
}

// return the value at the top of the stack
template <class T>
T Stack<T>::Peek (void) const
{
    // if the stack is empty, terminate the program
    if (top == -1)
    {
        cerr << "Attempt to peek at an empty stack!" << endl;
        exit(1);
    }
    return stacklist[top];
}


// test for an empty stack
template <class T>
int Stack<T>::StackEmpty(void) const
{
    // return the logical value top == -1
   return top == -1;
}

// test for a full stack
template <class T>
int Stack<T>::StackFull(void) const
{
    // return logical condition top == MaxStackSize-1
   return top == MaxStackSize-1;
}

// clear stack
template <class T>
void Stack<T>::ClearStack(void) 
{
    // reset top to -1
    top = -1;
}

#endif  // TEMPLATE_STACK_CLASS
