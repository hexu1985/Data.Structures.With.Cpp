#include <iostream.h>
#pragma hdrstop

#include "node.h"
#include "nodelib.h"

template <class T>
void LinkSort(T a[], int n)
{
    // set up the linked list ordlist to hold array items
    Node<T> *ordlist = NULL, *currPtr;
    int i;
    
    // insert the elements from the array to the list in order 
    for (i=0;i < n;i++)
        InsertOrder(ordlist, a[i]);
        
    // scan the list and copy the data values back to the array
    currPtr = ordlist;
    i = 0;
    while(currPtr != NULL)
    {
        a[i++] = currPtr->data;
        currPtr = currPtr->NextNode();
    }
    
    // delete all the nodes created for the ordered list
    ClearList(ordlist); 
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
    
    LinkSort(A,10);                     // sort the array
    cout << "Sorted array:     ";
    PrintArray(A,10);                   // print the array      
    cout << endl;
}

/*
<Run of Program 9.4>

Sorted array:     3  5  28  33  55  60  65  74  82  95
*/
