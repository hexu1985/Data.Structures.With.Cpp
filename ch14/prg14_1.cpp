#include <iostream.h>
#pragma hdrstop

// include files containing the sort algorithms
#include "arrsort.h"
#include "heapsort.h"
#include "treesort.h"
#include "toursort.h"
#include "random.h"
#include "ticks.h"

// enum type that describes initial state of array data
enum Ordering {randomorder, ascending, descending};

// enum type to indicate sort algorithm used
enum SortType {
                exchange, selection, bubble, insertion,
                tournament, tree, heap, quick
              };
        
// copy n element array y to array x
void Copy(int *x, int *y, int n)
{
    for(int i=0;i<n;i++)
        *x++ = *y++;
}

// general sort function that takes an array with the
// given ordering and implements the specified sort
void Sort(int a[], int n, SortType type, Ordering order)
{
    long time;
    
    cout << "Sorting " << n;
    // describe the ordering of the data
    switch(order)
    {
        case randomorder:   cout << " items. ";
                            break;
        case ascending:     cout << " items in ascending order. ";
                            break;
        case descending:    cout << " items in descending order. ";
                            break;
    }

    // check the clock to get starting time of the sort
    time = TickCount();

    // describe the type of sort and then execute it
    switch(type)
    {
        case exchange:
                        ExchangeSort(a,n);
                        cout << "Exchange sort: ";
                        break;  
        case selection:
                        SelectionSort(a,n);
                        cout << "Selection sort: ";
                        break;  
        case bubble:
                        BubbleSort(a,n);    
                        cout << "Bubble sort: ";
                        break;  
        case insertion:
                        InsertionSort(a,n);
                        cout << "Insertion sort: ";
                        break;  
        case tournament:
                        TournamentSort(a,n);
                        cout << "Tournament sort: ";
                        break;  
        case tree:
                        TreeSort(a,n);
                        cout << "Tree sort: ";
                        break;  
        case heap:
                        HeapSort(a,n);
                        cout << "Heap sort: ";
                        break;  
        case quick:
                        QuickSort(a,0,n-1);
                        cout << "Quicksort: ";
                        break;  
    }
    
    // compute the time by measuring the difference between the
    // starting time and current time. convert to seconds
    time = TickCount() - time;
    cout << time/60.0 << endl;
}

// run the sorts for n data values and the given ordering
void RunTest(int n, Ordering order)
{
    int i;
    int  *a, *b;
    SortType stype;
    RandomNumber rnd;
    
    // allocate memory for the two n element arrays a and b
    a = new int [n];
    b = new int [n];
    
    // determine which data ordering to use
    if (order == randomorder)
        // initialize array b with random integers
        for (i = 0; i < n; i++)
        {
            b[i] = rnd.Random(n);
        }
    else if(order == ascending)
        // sort data 0,1,2,3,...,n-1
        for (i = 0; i < n; i++)
        {
            b[i] = i;
        }
    else
        // sort data n-1,n-2,...,1,0
        for (i = 0; i < n; i++)
        {
            b[i] = n-1-i;
        }

    // copy data to a. execute each sort with specified order
    for(stype=exchange;stype <= quick;stype = SortType(stype+1))
    {
        Copy(a,b,n);
        Sort(a, n, stype, order);
    }
            
    // delete the two dynamic arrays
    delete [] a;
    delete [] b;
}

// sort 4000,8000,10000,150000 and 20000 random data
// items. then sort an ordered and unordered list with
// 20000 data items.
void main(void)
{
    // int nelts[5] = {4000,8000,10000,15000,20000},i;

	// values of n that will work under Windows 3.1. there
	// is a heap size limitation that is exceeded with the
	// values used in the text
    int nelts[5] = {400,800,1000,1500,2000},i;
    
    cout.precision(3);
    cout.setf(ios::fixed | ios::showpoint);
    
	for(i=0;i < 5;i++)
		RunTest(nelts[i],randomorder);
    
	// RunTest(20000,ascending);
	// RunTest(20000,descending);
	// reduce n for Windows 3.1
	RunTest(1850,ascending);
	RunTest(1850,descending);
}

/*
<Run of Program 14.1>

Sorting 4000 items.  Exchange sort: 12.233
Sorting 4000 items.  Selection sort: 7.300
Sorting 4000 items.  Bubble sort: 15.783
Sorting 4000 items.  Insertion sort: 5.667
Sorting 4000 items.  Tournament sort: 0.283
Sorting 4000 items.  Tree sort: 0.317
Sorting 4000 items.  Heap sort: 0.133
Sorting 4000 items.  Quicksort: 0.067

Sorting 8000 items.  Exchange sort: 49.950
Sorting 8000 items.  Selection sort: 29.433
Sorting 8000 items.  Bubble sort: 64.033
Sorting 8000 items.  Insertion sort: 23.150
Sorting 8000 items.  Tournament sort: 0.633
Sorting 8000 items.  Tree sort: 0.683
Sorting 8000 items.  Heap sort: 0.283
Sorting 8000 items.  Quicksort: 0.167

Sorting 10000 items.  Exchange sort: 77.467
Sorting 10000 items.  Selection sort: 46.017
Sorting 10000 items.  Bubble sort: 99.100
Sorting 10000 items.  Insertion sort: 35.433
Sorting 10000 items.  Tournament sort: 0.900
Sorting 10000 items.  Tree sort: 0.917
Sorting 10000 items.  Heap sort: 0.350
Sorting 10000 items.  Quicksort: 0.217

Sorting 15000 items.  Exchange sort: 173.967
Sorting 15000 items.  Selection sort: 103.000
Sorting 15000 items.  Bubble sort: 223.283
Sorting 15000 items.  Insertion sort: 80.233
Sorting 15000 items.  Tournament sort: 1.300
Sorting 15000 items.  Tree sort: 1.400
Sorting 15000 items.  Heap sort: 0.583
Sorting 15000 items.  Quicksort: 0.333

Sorting 20000 items.  Exchange sort: 313.333
Sorting 20000 items.  Selection sort: 185.050
Sorting 20000 items.  Bubble sort: 399.467
Sorting 20000 items.  Insertion sort: 143.667
Sorting 20000 items.  Tournament sort: 1.950
Sorting 20000 items.  Tree sort: 1.883
Sorting 20000 items.  Heap sort: 0.767
Sorting 20000 items.  Quicksort: 0.467

Sorting 20000 items in ascending order.  Exchange sort: 185.267
Sorting 20000 items in ascending order.  Selection sort: 185.783
Sorting 20000 items in ascending order.  Bubble sort: 0.033
Sorting 20000 items in ascending order.  Insertion sort: 0.050
Sorting 20000 items in ascending order.  Tournament sort: 1.767
Sorting 20000 items in ascending order.  Tree sort: 262.267
Sorting 20000 items in ascending order.  Heap sort: 0.750
Sorting 20000 items in ascending order.  Quicksort: 0.233

Sorting 20000 items in descending order.  Exchange sort: 526.167
Sorting 20000 items in descending order.  Selection sort: 199.000
Sorting 20000 items in descending order.  Bubble sort: 584.667
Sorting 20000 items in descending order.  Insertion sort: 286.917
Sorting 20000 items in descending order.  Tournament sort: 1.650
Sorting 20000 items in descending order.  Tree sort: 275.700
Sorting 20000 items in descending order.  Heap sort: 0.800
Sorting 20000 items in descending order.  Quicksort: 0.283
*/
