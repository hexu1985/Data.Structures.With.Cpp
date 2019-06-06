#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

#include "array.h"

void main(void)
{
    // array holding primes begins with 10 elements
    Array<int>  A(10);
    
    // user supplies upperlimit which determines range of primes
    int upperlimit, primecount = 0, i, j;
         
    cout << "Enter a value >= 2 as upper limit for prime numbers: ";
    cin >> upperlimit;
    
    A[primecount++] = 2;    // 2 is a prime
    for(i = 3; i < upperlimit; i++)
    {
        // if prime list is full, allocate 10 more elements
        if (primecount == A.ListSize())
            A.Resize(primecount + 10);

        // even numbers > 2 not prime. contine next iteration
        if (i % 2 == 0)
            continue;
        
        // check odd divisors 3,5,7,... up to i/2
        j = 3;
        while (j <= i/2 && i % j != 0)
            j += 2;
            
        // i prime if none of 3,5,7,... up to i/2 divides i
        if (j > i/2)
            A[primecount++] = i;
    }

    for (i = 0; i < primecount; i++)
    {
        cout << setw(5) << A[i];
        
        // output newline every 10 primes
        if ((i+1) % 10 == 0)
            cout << endl;
    } 
    cout << endl;
}

/*
<Run of Program 8.3>

Enter a value >= 2 as the upper limit for prime numbers: 100
    2    3    5    7   11   13   17   19   23   29
   31   37   41   43   47   53   59   61   67   71
   73   79   83   89   97
*/
