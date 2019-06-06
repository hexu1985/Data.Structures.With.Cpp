#include <iostream.h>
#pragma hdrstop

// include the linked list implementation of the SeqList
#include "seqlist1.h"

void main(void)
{
    // define an integer list
    SeqList<int> L;
    long  i;
    
    // initialize the list with values 0 .. 499
    for (i = 0; i < 500; i++)
        L.Insert(int(i));
        
    // exercise the delete/insert operations 50000 times
    cout << "Program begin!" << endl;
    for (i = 1; i <= 50000L; i++)
    {
        L.DeleteFront();
        L.Insert(0);
    }
    cout << "Program done!" << endl;
}

/*
<Run of Program 9.7b>

Program begin!
Program done!   // 4 seconds
*/
