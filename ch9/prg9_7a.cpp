#include <iostream.h>
#pragma hdrstop

// use DataType = int to store integer values in the list
typedef int DataType;

// include the array-based SeqList class
#include "aseqlist.h"

void main(void)
{
    // a list with capacity 500 integers
    SeqList L;
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
<Run of Program 9.7a>

Program begin!
Program done!       // 55 seconds

*/
