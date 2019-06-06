#include <iostream.h>
#pragma hdrstop

#include "permute.h"    // include function Permute
 
void main(void)
{
    // permlist contains the n numbers we permute
    int permlist[UpperLimit];
    int n,i;
            
    cout << "Enter a number 'n' between 1 and " 
         << UpperLimit << ": ";
    cin >> n;
    
    // initialize permlist to {1,2,3,...,n}
    for (i=0;i < n;i++)
        permlist[i] = i+1;
    cout << endl;
        
    // print permutations of elements in array
    // permlist from indices 0 to n-1    
    permute(permlist,0,n);
}
    
/*
<Run of Program 10.4>

Enter a number 'n' between 1 and 5: 3

1  2  3
1  3  2
2  1  3
2  3  1
3  1  2
3  2  1
*/
