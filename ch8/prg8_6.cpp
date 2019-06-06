#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

#include "set.h"		// use the Set class

// compute and print all primes <= n using the
// Sieve of Eratosthenes
void PrintPrimes(int n)
{
	// set(sieve) must handle values 2..n
	Set<int> S(n+1);
	int m, k, count;
	
	// insert all values 2..n into the set
	for(m=2;m <= n;m++)
		S.Insert(m);

	// look at all numbers from 2 to sqrt(n)
	for(m=2;m*m <= n;m++)
		// if m in S, delete all multiples of m from set
		if(S.IsMember(m))
			for(k=m+m;k <= n;k += m)
				if (S.IsMember(k))
					S.Delete(k);
	
	// all elements remaining in S are prime.
	// print the primes 10 per line
	count = 1;
	for(m=2;m <= n;m++)
		if (S.IsMember(m))
		{
			cout << setw(3) << m << "  ";
			if (count++ % 10 == 0)
				cout << endl;

		}
	cout << endl;
}

void main(void)
{
	int n;
	
	cout << "Enter n: ";
	cin >> n;
	cout << endl;
	
	PrintPrimes(n);
}

/*
<Run of Program 8.6>

Enter n: 100

  2    3    5    7   11   13   17   19   23   29
 31   37   41   43   47   53   59   61   67   71
 73   79   83   89   97
*/
