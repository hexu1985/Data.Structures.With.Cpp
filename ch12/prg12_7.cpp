#include <iostream.h>
#pragma hdrstop

#include "random.h"         // include random number generator
#include "houses.h"         // including the painting hierarchy

void main(void)
{
    // dynamic list of House addresses
    House *contractorList[5];
    RandomNumber rnd;
    
    // construct the list of 5 houses to be painted
    for (int i=0;i < 5;i++)
        // randomly choose house type 0, 1, 2, create the object,
        // and assign its address in contractorList.
        switch(rnd.Random(3))
        {
            case 0: contractorList[i] = new WoodFrameHouse;
                    break;
            case 1: contractorList[i] = new StuccoHouse;
                    break;
            case 2: contractorList[i] = new VinylSidedHouse;
                    break;
        }
    
    // paint houses using method Paint. since Paint is virtual,
    // dynamic binding is used, and the correct method is called.
    for (i=0;i < 5;i++)
    {
        contractorList[i]->Paint();
        cout << endl;
    }
}

/*
<Run of Program 12.7>

Painting a Stucco House
Painting a Vinyl Sided House
Painting a Wood Frame House
Painting a Vinyl Sided House
Painting a Stucco House
*/
