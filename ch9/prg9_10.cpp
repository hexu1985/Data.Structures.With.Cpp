#include <iostream.h>
#pragma hdrstop

#include "dnode.h"

template <class T>
void InsertLower(DNode<T> *dheader, DNode<T>* &currPtr, T item)
{
    DNode<T> *newNode= new DNode<T>(item), *p;
    
    // look for the insertion point
    p = currPtr;
    while (p != dheader && item < p->data)
        p = p->NextNodeLeft();

    // insert the item
    p->InsertRight(newNode);

    // reset currPtr to the new node
    currPtr = newNode;
}

template <class T>
void InsertHigher(DNode<T>* dheader, DNode<T>* & currPtr, T item)
{
    DNode<T> *newNode= new DNode<T>(item), *p;
    
    // look for the insertion point
    p = currPtr;
    while (p != dheader && p->data < item)
        p = p->NextNodeRight();

    // insert the item
    p->InsertLeft(newNode);

    // reset currPtr to the new node
    currPtr = newNode;
}

template <class T>
void DLinkSort(T a[], int n)
{
    // set up the doubly linked list to hold array items
    DNode<T> dheader, *currPtr;
    int i;
    
    // insert the first element in dlist 
    DNode<T>  *newNode = new DNode<T>(a[0]);
    dheader.InsertRight(newNode);
    currPtr = newNode;

    // insert the remaining elements in dlist 
    for (i=1;i < n;i++)
        if (a[i] < currPtr->data)
            InsertLower(&dheader,currPtr,a[i]);
        else
            InsertHigher(&dheader,currPtr,a[i]);

    // scan the list and copy the data values back to the array
    currPtr = dheader.NextNodeRight();
    i = 0;
    while(currPtr != &dheader)
    {
        a[i++] = currPtr->data;
        currPtr = currPtr->NextNodeRight();
    }
    
    // delete all nodes in the list
    while(dheader.NextNodeRight() != &dheader)
    {
        currPtr = (dheader.NextNodeRight())->DeleteNode();
        delete currPtr;
    }
}

// scan the array and print its elements
void PrintArray(int a[], int n)
{
    for(int i=0;i < n;i++)
        cout << a[i] << "  ";
}

void main(void)
{
    // initialized array with 10 integer values
    int A[10] = {82,65,74,95,60,28,5,3,33,55};
    
    DLinkSort(A,10);                     // sort the array
    cout << "Sorted array:     ";
    PrintArray(A,10);                   // print the array      
    cout << endl;
}

/*
<Run of Program 9.10>

Sorted array:     3  5  28  33  55  60  65  74  82  95
*/
