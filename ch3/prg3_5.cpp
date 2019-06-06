#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

#include "trimat.h"         // include the TriMat class

void main(void)
{
    int  n;
  
    // create a uniform matrix size
    cout << "What is the matrix size? ";
    cin >> n;
  
    // declare three n x n matrices
    TriMat A(n), B(n), C(n);

    // read matrices A and B
    cout << "Enter a " << n << " x " << n
    	 << " triangular matrix" << endl;
    A.ReadMat();
    cout << endl;
  
    cout << "Enter a " << n << " x " << n
    	 << " triangular matrix" << endl;
    B.ReadMat();
    cout << endl;

    // execute operations and print the result
    cout  << "The sum  A + B" << endl;
    C = A.AddMat(B);
    C.WriteMat();
    cout << endl;
    cout << "The determinant of A+B is " << C.DetMat() << endl;

}

/*
<Run of Program 3.9>

What is the matrix size? 4
Enter a 4 by 4 triangular matrix:
1 2 -4 5
0 2 4 1
0 0 3 7
0 0 0 5

Enter a 4 by 4 triangular matrix:
1 4 6 7
0 2 6 12
0 0 3 1
0 0 0 2

The sum  A + B
  2.000  6.000  2.000 12.000
  0.000  4.000 10.000 13.000
  0.000  0.000  6.000  8.000
  0.000  0.000  0.000  7.000

The determinant of A+B is 336.000
*/
