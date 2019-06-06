#include <iostream.h>
#pragma hdrstop

#include "ordlist.h"
#include "array.h"
#include "arriter.h"
#include "random.h"

// traverse an integer Array and print each item,
// 10 integers per line
void PrintList(Array<int>& A)
{
    // use the Array iterator 
    ArrayIterator<int> iter(A);
    int   count;
    
    // traverse the list  and print
    count = 1;
    for(iter.Reset();!iter.EndOfList();iter.Next(), count++)
    {
        cout << iter.Data() <<  "  ";
        // print the list, 10 data values per line
        if (count % 10 == 0)
            cout << endl;
    }
}

// delete items from ordered list L and insert into array A.
// update loadIndex which indentifies the next index
// in A
void Copy(OrderedList<int> &L, Array<int> &A, int &loadIndex)
{
    while (!L.ListEmpty())
        A[loadIndex++] = L.DeleteFront();
}   

void main(void)
{
    // create runs in A by using ordered list L
    Array<int>  A(100);
    OrderedList<int> L;
    
    // random number generator
    RandomNumber rnd; 
    
    int i, loadIndex = 0;
    
    // generate 100 random numbers in range 100 to 999. filter
    // them through a 25 element ordered list. when the list
    //  fills, copy the elements to array A using Copy
    for (i = 1; i <= 100; i++)
    {
        L.Insert(rnd.Random(900) + 100);
        if (i % 25 == 0)
            Copy(L,A,loadIndex);
    }
    
    // print the final array A containing the runs
    PrintList(A);
}


/*
<Run of Program 12.6>

110  116  149  152  162  240  345  370  422  492
500  532  578  601  715  730  732  754  815  833
850  903  929  947  958  105  132  139  139  190
205  216  221  243  287  348  350  445  466  507
513  524  604  634  641  730  784  940  969  982
296  375  412  437  457  466  507  550  594  652
725  728  771  799  803  815  859  879  909  915
940  990  991  992  994  101  118  123  155  310
343  368  372  434  443  489  515  529  557  574
641  739  774  784  829  875  883  922  967  972
*/
