#include <iostream.h>
#pragma hdrstop

#include "store.h"
#include "student.h"

void main(void)
{
    Student graduate = {1000, 23};
    Store<int> A, B;
    Store<Student> S;
    Store<double> D;

    A.PutElement(3);
    B.PutElement(-7);
    cout << A.GetElement() << "  " << B.GetElement() << endl;

    S.PutElement(graduate);
    cout << "The student id is " << S.GetElement().studID
    	 << endl;

    // D is not initialized
    cout << "Retrieving object D  " << D.GetElement() << endl;
}

/*
<Run of Program 7.2>

3  -7
The student id is 1000
Retrieving object D  No item present!
*/
