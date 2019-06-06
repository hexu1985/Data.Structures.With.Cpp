#include <iostream.h>
#pragma hdrstop

#include "cnode.h"
#include "random.h"

// create circular linked list with given header node
void CreateList(CNode<int> *header, int n)
{
    // begin inserting after the header
    CNode<int> *currPtr = header, *newNodePtr;
    int i;
    
    // build the n element circular list
    for(i=1;i <= n;i++)
    {
        // allocate node with data value i
        newNodePtr = new CNode<int>(i);
        
        // insert at end of the list and advance currPtr to end
        currPtr->InsertAfter(newNodePtr);
        currPtr = newNodePtr;
    }
}

// given an n item circular list, solve the Josephus problem
// by deleting every m th person until only one remains.
void Josephus(CNode<int> *list, int n, int m)
{
    //prevPtr trails currPtr around the list.
    CNode<int> *prevPtr = list, *currPtr = list->NextNode();
    
    CNode<int> *deletedNodePtr;
    
    // delete all but one person from the list
    for(int i=0;i < n-1;i++)
    {
        // counting current person at currPtr, visit m persons.
        // we must advance m-1 times.
        for(int j=0;j < m-1;j++)
        {
            // advance the pointers
            prevPtr = currPtr;
            currPtr = currPtr->NextNode();
            
            // if currPtr at the header, move pointers again
            if (currPtr == list)
            {
                prevPtr = list;
                currPtr = currPtr->NextNode();
            }
        }

        cout << "Delete person " << currPtr->data << endl;
        
        // record node to delete and advance currPtr
        deletedNodePtr = currPtr;
        currPtr = currPtr->NextNode();
        
        // delete node from the list
        prevPtr->DeleteAfter();
        delete deletedNodePtr;
        
        // if currPtr at the header, move pointers again
        if (currPtr == list)
        {
            prevPtr = list;
            currPtr = currPtr->NextNode();
        }
    }
    
    cout << endl << "Person " << currPtr->data
         << " wins the cruise." << endl;
    
    // delete the one remaining node
    deletedNodePtr = list->DeleteAfter();
    delete deletedNodePtr;
}

void main(void)
{
    // the list of persons
    CNode<int> list;
    
    // n is number of persons, m is rotation selector
    int n, m;
    // use to generate random value 1 <= m <= n
    RandomNumber rnd;
    
    cout << "Enter the number of contestants? ";
    cin >> n;
    
    // create circular list with persons 1, 2, ... n
    CreateList(&list,n);

    m = 1+rnd.Random(n);
    cout << "Generated the random number " << m << endl;
    
    // solve the Josephus problem and print the cruise winner
    Josephus(&list,n,m);
}

/*
<Run of Program 9.9>

Enter the number of contestants? 10
Generated the random number 5
Delete person 5
Delete person 10
Delete person 6
Delete person 2
Delete person 9
Delete person 8
Delete person 1
Delete person 4
Delete person 7

Person 3 wins the cruise.
*/
