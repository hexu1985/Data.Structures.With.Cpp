#include <iostream.h>
#pragma hdrstop

#include "link.h"       // include the linked list class
#include "random.h"

// print list L
template <class T>
void PrintList(LinkedList<T>& L)
{
    // move to front of L. traverse list and print each element
    for(L.Reset(); !L.EndOfList(); L.Next())
        cout << L.Data() << "  ";
}

void RemoveDuplicates(LinkedList<int>& L)
{
    // current list position and data value
    int currPos, currValue;
    
    // move to the front of the list
    L.Reset();
    
    // cycle through the list
    while(!L.EndOfList())
    {
        // record the current list data value and its position
        currValue = L.Data();
        currPos = L.CurrentPosition();
        
        // move one node to the right
        L.Next();
        
        // move forward until end of list, deleting
        // all occurrences of currValue
        while(!L.EndOfList())
            // if node deleted, current position is next node
            if (L.Data() == currValue)
                L.DeleteAt();
            else
                L.Next();               // move to the next node
                
        // move to first node with value currValue. go forward
        L.Reset(currPos);
        L.Next();
    }
}
        
void main(void)
{
    LinkedList<int> L;
    int i;
    RandomNumber rnd;
    
    // insert 15 random integers in range 1-7 and print list
    for(i=0; i < 15; i++)
        L.InsertRear(1+rnd.Random(7));
    cout << "Original list: ";
    PrintList(L);
    cout << endl;
        
    // remove all the duplicate data values and print new list
    RemoveDuplicates(L);
    cout << "Final list:    ";
    PrintList(L);
    cout << endl;
}

/*
<Run of Program 9.6>

Original list: 1  7  7  1  5  1  2  7  2  1  6  6  3  6  4
Final list:    1  7  5  2  6  3  4
*/
