#include <iostream.h>
#pragma hdrstop

#include "node.h"
#include "nodelib.h"
#include "random.h"

void main(void)
{
    // set list head to NULL
    Node<int> *head = NULL, *currPtr;
    
    int i, key, count = 0;
    RandomNumber rnd;

    // insert 10 random integers at front of list
    for (i=0;i < 10;i++)
        InsertFront(head, int(1+rnd.Random(10)));
        
    // print the original list
    cout << "List: ";
    PrintList(head,noNewline);
    cout << endl;
    
    // prompt user for an integer key
    cout << "Enter a key: ";
    cin >> key;
    
    // cycle through the list
    currPtr = head;
    while (currPtr != NULL)
    {
        // if data matches key, increment count
        if (currPtr->data == key)
            count++;
            
        // move to the next node of the list         
        currPtr = currPtr->NextNode();
    }
    
    cout << "The data value " << key << " occurs " << count
         << " times in the list" << endl;
}

/*
<Run of Program 9.1>

List: 3  6  5  7  5  2  4  5  9  10
Enter a key: 5
The data value 5 occurs 3 times in the list
*/
