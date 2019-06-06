#include <iostream.h>
#include <stdlib.h>
#pragma hdrstop

#include "rational.h"           // include the Rational class

// print a Rational number as a mixed number (+/-)N p/q
void PrintMixedNumber (Rational x)
{
    // whole part of the Rational number x
	int wholepart = int(x.GetNumerator() / x.GetDenominator());
	
    // stores the fractional part of the mixed number
    Rational fractionpart = x - Rational(wholepart);
    
    // if no fractional part, print integer
    if (fractionpart == Rational(0))
        cout << wholepart << "  ";
    else
    {
        // reduce fractional part
        fractionpart.Reduce();
        // print sign with the whole part
        if (wholepart < 0)
            fractionpart = -fractionpart;
        if (wholepart != 0)
            cout << wholepart << " " << fractionpart << "  ";
        else
            cout << fractionpart << "  ";
    }
}

// solve ax + b = c, where a, b, c are rational numbers
Rational SolveEquation(Rational a, Rational b, Rational c)
{
    // check to see if a is 0
    if (a == Rational(0))
    {
        cout << "Equation has no solution." << endl;
        // return Rational(0) if there is no solution.
        return Rational(0);
    }
    else
        return (c-b)/a;
}

void main(void)
{
    Rational r1, r2, r3, ans;
    
    cout << "Enter coefficients for "
                "'a/b X + c/d = e/f': ";
    cin >> r1 >> r2 >> r3;
    
    cout << "Simplified equation: " << r1 << " X = "
         << (r3-r2) << endl;
    ans = SolveEquation(r1,r2,r3);
    ans.Reduce();
    cout << "X = " << ans << endl;
    
    cout << "Solution as a mixed number: ";
    PrintMixedNumber(ans);
    cout << endl;
}
 
/*
<Run #1 of Program 6.2>

Enter coefficients for 'a/b X + c/d = e/f': 2/3 2/1 4/5
Simplified equation: 2/3 X = -6/5
X = -9/5
Solution as a mixed number: -1 4/5

<Run #2 of Program 6.2>

Enter coefficients for 'a/b X + c/d = e/f': 2/3 -7/8 -3/8
Simplified equation: 2/3 X = 32/64
X = 3/4
Solution as a mixed number: 3/4
*/
