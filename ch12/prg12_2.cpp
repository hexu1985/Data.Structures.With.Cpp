#include <iostream.h>
#include <string.h>
#pragma hdrstop

#include "animal.h"

void main(void)
{
    Animal A("reptile"), *p;
    Cat C("domestic", "warm blooded");
    Tiger T("bengal", "wild", "meat eating");
    
    // static binding. Announce1 has value Animal parameter.
    // since T is a Tiger, function executes Animal Identify
    Announce1(T);       // static binding; calls Animal method

    // examples of polymorphism. since parameter is a pointer,
    // Announce2 uses dynamic binding to execute Identify method
    // of the actual object parameter
    Announce2(&A);      // dynamic binding; calls Animal method
    Announce2(&C);      // dynamic binding; calls Cat method
    Announce2(&T);      // dynamic binding; calls Tiger method


    // direct call to the Identify method in the animal class
    A.Identify();       // static binding
    cout << endl;
    
    // dynamic binding; call made to the Cat method
    p = &C;
    p->Identify();
    cout << endl;
    
    // assignment of Tiger object to Animal object.
    // copy inherited animal data
    A = T;
    A.Identify();       // identify animal data from Tiger T
    cout << endl;
}

/*
<Run of Program 12.2>

In static Announce1,  calling Identify:
I am a meat eating animal

In dynamic Announce2, calling Identify:
I am a reptile animal

In dynamic Announce2, calling Identify:
I am a warm blooded animal
I am a domestic cat

In dynamic Announce2, calling Identify:
I am a meat eating animal
I am a wild cat
I am a bengal tiger

I am a reptile animal

I am a warm blooded animal
I am a domestic cat

I am a meat eating animal
*/
