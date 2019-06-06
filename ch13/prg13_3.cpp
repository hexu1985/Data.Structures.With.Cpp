#include <iostream.h>
//#pragma hdrstop

// include the random number generator and the filter class
#include "random.h"
#include "longrun.h"

// copy array A to array B
void CopyArray(int A[], int B[], int n)
{
	for (int i = 0; i < n; i++)
		B[i] = A[i];
}

void main()
{
    // an 15 element integer array to illustrate the filter
    int demoArray[15];
    
    // large 10000 element arrays to count runs 
    int *A = new int[10000], *B = new int[10000];
    RandomNumber rnd;
    
    // filters will have size 5, 50 (5*10), and 500 (5 * 100)
    int  i, filterSize = 5;
    
    // create a list of 15 random integers; set up filter
    for (i = 0; i < 15; i++)
    	demoArray[i] = rnd.Random(100);
    cout << endl;
    LongRunFilter<int> F(demoArray, 15, 4);
    
    // print the list before and after creating long
    // runs with a 4 element filter 
	cout << "Raw List" << endl;
    F.PrintRuns();
    cout << endl;
    F.LoadRuns();
    cout << "Filtered List" << endl;
    F.PrintRuns();
    cout << endl;
    
    // initialize an array with 10000 random integers
    for (i = 0; i < 10000; i++)
        A[i] = rnd.Random(25000);
    
    cout << "Runs with 3 filters" << endl;
    // set up a raw list and count the number of runs     
    LongRunFilter<int>  LR(A, 10000, 0);
    cout << "Number of runs in initial 100000 element array is " 
    	 << LR.CountRuns() << endl;
        
    // test filter size 5, 50, and 500 and count the runs
    for (i = 0; i < 3; i++)
    {
    	CopyArray(A,B,10000);
    	LongRunFilter<int>  LR(B, 10000, filterSize);
    
		// create the long runs
    	LR.LoadRuns();
     	cout << "  Total runs with a filter of " << filterSize 
     		 << " is " << LR.CountRuns() << endl;
     
     	// increase the filter size ten-fold
     	filterSize *= 10;
     }
}
 
/*
<Run of Program 13.3>
Raw List:  99  15  68  16  90  43  1  76  77  18  30  22  5  80  39  
99  
15   68   
16   90   
43   
1   76   77   
18   30   
22   
5   80   
39   

Filtered List
15  16   43   68   76   77   90   99   
1   5   18   22   30   39   80   

Runs with 3 filters
Number of runs in initial 100000 element array is 4978
  Total runs with a filter of 5 is 990
  Total runs with a filter of 50 is 101
  Total runs with a filter of 500 is 11
*/
