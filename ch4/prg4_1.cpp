#include <iostream.h>
#pragma hdrstop

typedef int DataType;       // integer data

#include "dsearch.h"
#include "random.h"
#include "ticks.h"

// sort the n element integer array in ascending order
void ExchangeSort(int a[], int size)
{
    int i, j, temp;
    
    // with n-1 passes, place correct values in a[0]..a[n-1]
    for (i = 0; i < size-1; i++)
        // put minimum of a[i+1]...a[n-1] in a[i]
        for (j = i+1; j < size; j++)
            // if a[j] < a[i], exchange them
            if (a[j] < a[i])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}

void main(void)
{
    // A holds list to search, B holds the keys
    int A[1000], B[500];
    int i, matchCount;
    
    // used for timing data
    long tcount;
    
    RandomNumber rnd;
    
    // create array A with 1000 random values between 0..1999 
    for (i = 0; i < 1000; i++)
        A[i] = rnd.Random(2000);
    ExchangeSort(A,1000);
    
    // generate 500 random keys in the same range
    for (i = 0; i < 500; i++)
        B[i] = rnd.Random(2000);
        
    cout << "Timing the Sequential Search" << endl;
    tcount = TickCount();       // starting time
    matchCount = 0;
    for (i = 0; i < 500; i++)
        if (SeqSearch(A,1000, B[i]) != -1)
            matchCount++;
    tcount = TickCount() - tcount;  // number of 1/60 th secs.
    cout << "Sequential Search takes " << tcount/60.0 
         << " seconds for " << matchCount << " matches." << endl;
    
    cout << "Timing the Binary Search" << endl;
    tcount = TickCount();       // starting time
    matchCount = 0;
    for (i = 0; i < 500; i++)
        if (BinSearch(A,0,999,B[i]) != -1)
            matchCount++;
    tcount = TickCount() - tcount;  // number of 1/60 th secs.
    cout << "Binary Search takes " << tcount/60.0
         << " seconds for " << matchCount << " matches." << endl;
}

/*
<Run of Program 4.1>

Timing the Sequential Search
Sequential Search takes 0.816667 seconds for 181 matches.
Timing the Binary Search
Binary Search takes 0.016667 seconds for 181 matches.
*/
