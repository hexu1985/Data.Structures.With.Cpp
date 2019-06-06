#include <iostream.h>
#pragma hdrstop
// suppress parameter not used message caused by line 9
#pragma warn -par

#include "dynamic.h"

template <class T>
DynamicClass<int> Demo(DynamicClass<T> one, DynamicClass<T>& two, T m)
{
    // calls the constructor (member1= m, *member2= m)
    DynamicClass<T> obj(m,m);

	// a copy of obj is made and returned as the
	// value of the function
	return obj;

    // the temporary objects T and one are destroyed upon
    // return from Demo.
}

void main()
{
	/*	A(3,5) calls the constructor (member1=3, *member2=5)
	
		B = A calls copy constructor to initialize object B 
		from object A. (member1=3, *member2=5)
			
		object C calls the constructor (member1=0, *member2=0) */
    DynamicClass<int> A(3,5), B = A, C(0,0);
    
	/*	call the function Demo. the copy constructor is used to create
		the value parameter one (member1=3, *member2=5) by copying
		object A. parameter two is passed by reference, so the copy
		constructor is not called. upon return, a copy is made
		of the local object obj. this copy is assigned to object C */
    C = Demo(A,B,5);
    
    // all remaining objects are destroyed upon program exit.
}

/*
<Run of Program 8.2>

Constructor: 3/5
Copy Constructor:  3/5
Constructor: 0/0
Copy Constructor:  3/5
Constructor: 5/5
Copy Constructor:  5/5
Destructor: 5/5564
Destructor: 3/5556
Assignment Operator: 5/5
Destructor: 5/5
Destructor: 5/5
Destructor: 3/5
Destructor: 3/5
*/
