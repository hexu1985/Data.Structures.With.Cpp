
#include <iostream.h>
#pragma hdrstop

#include "temp.h"	// "temp.h" contains Temperature class

void main(void)
{
    // initialize the temperature object (high=70, low=50)
    Temperature today (70,50);
    float temp; 
            
    cout << "Enter the noon temperature: ";
    cin >> temp;
    
    // update object to include noon temperature
    today.UpdateTemp(temp);
    cout << "At noon: High " << today.GetHighTemp();
    cout << "  Low " << today.GetLowTemp() << endl;
    
    cout << "Enter the evening temperature: ";
    cin >> temp;
    
    // update object to include evening temperatures
    today.UpdateTemp(temp);
    cout << "Today's High " << today.GetHighTemp();
    cout << "  Low " << today.GetLowTemp() << endl;
}

/*
<Run of Program 3.2>

Enter the noon temperature: 80
At noon: High 80  Low 50
Enter the evening temperature: 40
Today's High 80  Low 40
*/
