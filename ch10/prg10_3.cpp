#include <iostream.h>
#pragma hdrstop

#include "comm.h"        // include the function comm

void main (void)
{
    int n, k;
    
    cout << "Enter # of candidates and # on a committee: ";
    cin >> n >> k;
    
    cout << "The # of possible committees is " 
         << comm(n,k) << endl;
}

/*
<Run #1 of Program 10.3>

Enter # of candidates and # on a committee: 10 4
The # of possible committees is 210

<Run #2 of Program 10.3>

Enter # of candidates and # on a committee: 9 0
The # of possible committees is 1
*/
