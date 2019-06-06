#include <math.h>

const double sqrt5 = sqrt(5.0);

// compute nth Fibonacci number using the algebraic formula
double FibFormula(int n)
{
    double p1, p2;
    
    // C++ math library function 
    //        double pow(double x, double y);
    // computes x to the power y
    p1 = pow((1+sqrt(5))/2.0,n);
    p2 = pow((1-sqrt(5))/2.0,n);
    return (p1 - p2)/sqrt(5);
}

// compute nth Fibonacci number iteratively
// this is an O(n) algorithm
long FibIter(int n)
{
    long twoback = 1, oneback = 1, current;
    int i;
    
    // FibIter(1) = FibIter(2) = 1
    if (n == 1 || n == 2)
        return 1;
        
    // current = twoback + oneback, n >= 3
    else
        for (i=3;i <= n;i++)
        {
            current = twoback + oneback;
            twoback = oneback;
            oneback = current;
        }
        
    return current;
}

// recursive generation of the nth Fibonacci number
// this is an exponential algorithm!
long Fib(int n)
{
    // stopping condition: f1 = f2 = 1
    if (n == 1 || n == 2)
        return 1;
        
    // recursive step: Fib(n) = Fib(n-2) + Fib(n-1)
    else
        return Fib(n-1) + Fib(n-2);
}
