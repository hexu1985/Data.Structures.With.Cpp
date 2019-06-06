#include <iostream.h>
#pragma hdrstop

#include "heap.h"

// print the  array of n elements
template <class T>
void PrintList (T A[], int n)
{   
    for(int i=0;i < n;i++)
        cout << A[i] << "  ";
    cout << endl;
}

void main(void)
{
    // initialized array of 10 elements
    int A[10] = {50, 20, 60, 65, 15, 25, 10, 30, 4, 45};

    cout << "Initial array:" << endl;
    PrintList(A,10);

    // declare a heap that binds array A as its list    
    Heap<int>  H(A,10);
    
    // print the heapified version of array A
    cout << "Heapified array:" << endl;
    PrintList(A,10);
    
    cout << "Deleting elements from the heap:" << endl;
    // repeatedly extract smallest value
    while(!H.ListEmpty())
        cout << H.Delete() << "  ";
    cout << endl;
}

/* 
<Run of Program 13.1>

Initial array:
50  20  60  65  15  25  10  30  4  45  
Heapified array:
4  15  10  20  45  25  60  30  65  50  
Deleting elements from the heap:
4  10  15  20  25  30  45  50  60  65  
*/
