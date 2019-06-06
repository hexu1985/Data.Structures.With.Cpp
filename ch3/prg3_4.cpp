
#include <iostream.h>
#pragma hdrstop

#include "date.h"               // include the Date class

void main (void)
{
    // Date objects with integer, default and string parmeters
    Date day1(6,6,44);          // June 6, 1944
    Date day2;                  // January 1, 1900
    Date day3("12/31/99");      //  December 31, 1999  
    
    
    cout << "D-Day in World War II - ";
    day1.PrintDate();
    cout << endl;                   
    cout << "The first day in the 20th century - ";
    day2.PrintDate();
    cout << endl;                   
    cout << "The last day in the 20th century - ";
    day3.PrintDate();
    cout << endl;                   
}

/*
<Run of Program 3.4>

D-Day in World War II - June 6, 1944
The first day in the 20th century - January 1, 1900
The last day in the 20th century - December 31, 1999
*/
