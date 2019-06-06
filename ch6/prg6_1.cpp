#include <iostream.h>
#pragma hdrstop

#include "rational.h"       // include the rational number class

// each operation is accompanied by output
void main(void)
{
    Rational r1(5), r2, r3;
    float    f;
    
    cout << "1. Rational value for integer 5 is " << r1 << endl;
    
    cout << "2. Enter a rational number: ";
    cin >> r1;
    f = float(r1);
    cout << "      Floating point equivalent is " << f << endl;
    
    cout << "3. Enter two rational numbers: ";
    cin >> r1 >> r2;
	cout << "      Results: " << (r1+r2) << " (+)   "
		 << (r1-r2) << " (-)   " <<  (r1*r2) << " (*)   "
         <<  (r1/r2) << " (/)   " << endl;  
    
    if (r1 < r2)
        cout << "      Relation (less than): " << r1 << " < "
             << r2 << endl;
    else if (r1 == r2)
        cout << "      Relation (equal to): " << r1 << " == "
             << r2 << endl;
    else 
        cout << "      Relation (greater than): " << r1 << " > "
             << r2 << endl;

    cout << "4. Input a floating point number: ";
    cin >> f;
    r1 = f;
    cout << "      Convert to Rational " << r1 << endl;
    f = r1;
    cout << "      Reconvert to float " << f << endl;
}
 
/*
<Run of Program 6.1>

1. Rational value for integer 5 is 5/1
2. Enter a rational number: -4/5
      Floating point equivalent is -0.8
3. Enter two rational numbers: 1/2 -2/3
      Results: -1/6 (+)   7/6 (-)   -2/6 (*)   -3/4 (/)
      Relation (greater than): 1/2 > -2/3
4. Input a floating point number: 4.25
      Convert to Rational 17/4
      Reconvert to float 4.25
*/
