#ifndef STACK_CLASS
#define STACK_CLASS

#include <iostream.h>
#include <stdlib.h>

const int MaxStackSize = 50;

class Stack
{
    private:
        // private data members. stack array, and top
        DataType stacklist[MaxStackSize];
        int top;
    public:
        // constructor; initialize the top
        Stack (void);
        
        // stack modification operations
        void Push (const DataType& item);
        DataType Pop (void);
        void ClearStack(void);
        
        // stack access
        DataType Peek (void) const;
        
        // stack test methods
        int StackEmpty(void) const;
        int StackFull(void) const;      // array implementation
};

// initialize stack top.
Stack::Stack (void) : top(-1)
{}

// push item on the the stack
void Stack::Push (const DataType& item)
{
    // if stacklist is full, terminate the program
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
DataType Stack::Pop (void)
{
    DataType temp;

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
DataType Stack::Peek (void) const
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
int Stack::StackEmpty(void) const
{
    // return the logical value top == -1
   return top == -1;
}

// test for a full stack
int Stack::StackFull(void) const
{
   // test the position of top
   return top == MaxStackSize-1;
}

// clear all items from the stack
void Stack::ClearStack(void) 
{
    top = -1;
}

#endif  // STACK_CLASS
