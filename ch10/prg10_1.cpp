#include <iostream.h>

// compute n! = n*(n-1)*(n-2)...(2)(1), 0!=1 recursively
long Factorial(long n)
{
    // if n == 0, then 0! = 1; otherwise, n! = n*(n-1)!
    if (n == 0)
        return 1;
    else
        return n * Factorial(n - 1);
}

void main (void)
{
    int i, n;
    
    // enter 4 positive integers and compute n! for each
    cout << "Enter 4 positive integers: ";
    for (i = 0; i < 4; i++)
    {
        cin >> n;
        cout <<  n << "! = " << Factorial(n) << endl;
    }
}

/*
<Run of Program 10.1>

Enter 4 positive integers: 0 7 1 4
0! = 1
7! = 5040
1! = 1
4! = 24
*/
