#include <iostream.h>
#pragma hdrstop

#include "graphlib.h"
#include "geometry.h"

void main(void)
{
    // declare objects C, D with fill patterns 7 and no fill
    Circle C(1.0,1.0,0.5,7), D(2.0,1.0,.33);
    char eol;        // used to delay before drawing figures
    
    cout << "Coordinates of C are  "<< C.GetX() << " and "
         << C.GetY() << endl;

    cout << "Circumference of C is " << C.Perimeter()
		 << endl;
    cout << "Area of C is " << C.Area() << endl;
    cout << "Type <return> to view figures:";
    cin.get(eol);    // wait until newline is typed
    
    // system dependent call to initialize the drawing surface.
    InitGraphics();
    
    // draw circle C with fill pattern 7 and radius 0.5
    C.Draw();
    // draw circle D with default fill pattern 0 and radius 0.33
    D.Draw();
    
    // relocate circle D to (1.5,1.8); radius to 0.25; fill to 11
    D.SetPoint(1.5,1.8);
    D.SetRadius(.25);
    D.SetFill(11);
    D.Draw();

    // delay for client input and shut down graphics
    ViewPause();
    ShutdownGraphics();
}

/*
<Run of Program 12.1>

Coordinates of C are  1 and 1
Circumference of C is 3.14159
Area of C is 0.785398
Type <return> to view figures:
*/
