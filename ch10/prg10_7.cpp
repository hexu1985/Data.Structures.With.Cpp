#include <iostream.h>
#pragma hdrstop

#include "fib.h"

void main(void)
{
    // print output from FibFormula as a fixed point
    // number, no decimal places
    cout.setf(ios::fixed);
    cout.precision(0);
    
    // print 35th Fibonacci number three ways
    cout << FibFormula(35) << endl;
    cout << FibIter(35) << endl;
    cout << Fib(35) << endl;
}

/*
<Run of Program 10.7>

9227465        <formula < 1-second>
9227465        <iterative function < 1-second>        
9227465        <recursive function 82+ seconds>
*/
