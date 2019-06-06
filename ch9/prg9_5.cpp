#include <iostream.h>
#pragma hdrstop

#include "link.h"           // include the linked list class
#include "random.h"

// position the list L at its maximum element
template <class T>
void FindMax(LinkedList<T> &L)
{
    if (L.ListEmpty())
    {
        cerr << "FindMax: list empty!" << endl;
        return;
    }

    // reset to start of the list
    L.Reset();
    
    // record first list value as current maximum with position 0
    T max = L.Data();
    int maxLoc = 0;
    
    // move to second data value and scan the list
    for (L.Next(); !L.EndOfList(); L.Next())
        if (L.Data() > max)
        {
            // new maximum. record value and the list position
            max = L.Data();
            maxLoc = L.CurrentPosition();
        }
        
    // reset the list back to the maximum value
    L.Reset(maxLoc);
}

// print list L
template <class T>
void PrintList(LinkedList<T>& L)
{
    // move to front of L. traverse list and print each element
    for(L.Reset(); !L.EndOfList(); L.Next())
        cout << L.Data() << "  ";      
}

void main(void)
{
    // list L is placed in sorted order in list K
    LinkedList<int> L, K;
    RandomNumber rnd;
    int i;
    
    // L is a list of 10 random integers in range 0-99
    for(i=0; i < 10; i++)
        L.InsertRear(rnd.Random(100));

    cout << "Original list: ";
    PrintList(L);
    cout << endl;
    
    // delete data from L until it is empty, inserting into K
    while (!L.ListEmpty())
    {
        // locate max of remaining elements
        FindMax(L);
        
        // insert max at front of list K and delete it from L
        K.InsertFront(L.Data());
        L.DeleteAt();
    }
    
    cout << "Sorted list:   ";
    PrintList(K);
    cout << endl;
}

/*
<Run of Program 9.5>

Original list: 82  72  62  3  85  33  58  50  91  26
Sorted list:   3  26  33  50  58  62  72  82  85  91
*/
