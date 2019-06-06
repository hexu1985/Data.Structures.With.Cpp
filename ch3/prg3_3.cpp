#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop
// suppress nuisance warning message caused by line 44
#pragma warn -sig 

#include "random.h"		// use random number generator

// toss numberCoins and return the total number of heads
int TossCoins(int numberCoins)
{
	// used for random toss of coins
    static RandomNumber coinToss;
    int i, tosses = 0;

    for (i=0;i < numberCoins;i++)
		// Random(2) = 1 indicates head
        tosses += coinToss.Random(2);
    return tosses;
}

void main(void)
{
    // number of coins per toss and number of tosses
    const int NCOINS = 10;
    const long NTOSSES = 50000L;
    
    // heads[0] = number of 0 heads, heads[1] one head, etc.
    long i, heads[NCOINS + 1];
    
    int  j, position; 

    // Initialize the array tosses
    for (j=0;j < NCOINS+1;j++)
        heads[j]  = 0;

    // toss coins 50,000 times and record results in array heads
    for (i=0;i < NTOSSES;i++)
        heads[TossCoins(NCOINS)]++;

    // Print out the frequency graph
    for (i=0; i <= NCOINS;i++)
    {
        position = int(float(heads[i])/NTOSSES * 72);
        cout << setw(6) << i << "  ";
        for (j = 0; j < position-1;j++)
            cout << " ";
		// '*' relative number of tosses resulting in i heads. 
        cout << "*" << endl;
    }   
}

/*

<Run of Program 3.3>

     0  *
     1  *
     2    *
     3         *
     4               *
     5                  *
     6               *
     7         *
     8    *
     9  *
    10  *
*/
