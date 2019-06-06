#include <iostream.h>
#pragma hdrstop

#include "dynamic.h"

void DestroyDemo(int m1, int m2)
{
    DynamicClass<int> obj(m1,m2);
}

void main(void)
{
    // create automatic object Obj_1 with member1=1, *member2=100
    DynamicClass<int> Obj_1(1,100);
    
    // declare a pointer to an object
    DynamicClass<int> *Obj_2;
    
    // allocate dynamic object pointed to by Obj_2 with
	// member1 = 2 and *member2 = 200
    Obj_2 = new DynamicClass<int>(2,200);
    
    // call function DestroyObject with parameters 3/300
    DestroyDemo(3,300);
        
    // explicitely delete Obj_2
    delete Obj_2;
    
    cout << "Ready to exit program." << endl;
}

/*
<Run of Program 8.1>

Constructor: 1/100
Constructor: 2/200
Constructor: 3/300
Destructor: 3/300
Destructor: 2/200
Ready to exit program.
Destructor: 1/100
*/
