#include <iostream.h>
#pragma hdrstop

#include "random.h"
#include "arrsort.h"
#include "toursort.h"
#include "heapsort.h"
#include "ticks.h"			// for TickCount

// prints the first 5 and last 5 items in the array
void PrintFirst_Last(int a[], int n)
{
    int i;
    
    for(i=0;i < 5;i++)
        cout << a[i] << "  ";
    cout << ". . .  ";
    for(i= n-5; i < n; i++)
        cout << a[i] << "  ";
    cout << endl;
}

enum SortType {heap,tournament,exchange};

void TimeSort(int *A, int n,
              char *sortName, SortType sort)
{
    long tcount;

    // TickCount is a system dependent function. it returns
    // the number of 1/60 th secs. since system startup.    
    
    cout << "Sorting with " << sortName << ':' << endl;
    
    // start the count then sort array A.  assign to 
    // tcount the elapsed sort time t in 1/60 th secs.
    tcount = TickCount();
    switch(sort)
    {
        case heap:          HeapSort(A,n);
                            break;
        case tournament:    TournamentSort(A,n);
                            break;
        case exchange:      ExchangeSort(A,n);
                            break;
    }
    tcount = TickCount() - tcount;
    
    // print the first 5 and last 5 elements of sorted array
    PrintFirst_Last(A,n);
    
    cout << sortName << " time is " << tcount << endl << endl;
}

void main(void)
{
    // pointers for arrays A, B, and C 
    int  *A, *B, *C;    
    RandomNumber rnd;
    
    // dynamically allocate memory and load arrays
    A = new int [2000];
    B = new int [2000];
    C = new int [2000];
    
    // load the arrays with 2000 identical random numbers 
    for(int i=0;i < 2000;i++)
        A[i] = B[i] = C[i] = rnd.Random(10000);
        
    TimeSort(A,2000,"Heap sort",heap);
    delete [] A;
    
    // repeat process for the tournament sort
    TimeSort(B,2000,"Tournament sort",tournament);
    delete [] B;
  
    // repeat process for the exchange sort
    TimeSort(C,2000,"Exchange sort",exchange);
    delete [] C;
}

/*
 
<Run of Program 13.2>

Sorting with Heap sort:
9993  9992  9984  9980  9978  . . .  11  9  9  5  1  
Heap sort time is 16

Sorting with Tournament sort:
1  5  9  9  11  . . .  9978  9980  9984  9992  9993  
Tournament sort time is 36

Sorting with Exchange sort:
1  5  9  9  11  . . .  9978  9980  9984  9992  9993  
Exchange sort time is 818
*/
