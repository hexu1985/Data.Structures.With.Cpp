#include <iostream.h>
#pragma hdrstop

#include "graphlib.h"
#include "geometry.h"

void main(void)
{
    // Circle C is centered at (3,1) with radius 0.25; 
    // variable three is a shape pointer to circle C 
    Circle C(3,1,.25, 11);
    Shape *one, *two, *three = &C;
    char eol;
    
    // Circle *one is centered at (1,1) with radius 0.5.
    // Rectangle *two based at (2,2) with length = width = 0.5.
    one = new Circle(1,1,.5,4);
    two = new Rectangle(2,2,.5,.5,6);
    
    cout << "Area/perimeter of C and figures one-three:" << endl;
    cout << "C: " << C.Area() << "  " << C.Perimeter() << endl;
    cout << "one: " << one->Area() << "  "
         << one->Perimeter() << endl;
    cout << "two: " << two->Area() << "  "
         << two->Perimeter() << endl;
    cout << "three: "<< three->Area() << "  "
         << three->Perimeter() << endl;
    
    cout << "Type <return> to view figures." << endl;
    cin.get(eol);
    
    // initialize the graphics system
    InitGraphics();
    
    one->Draw();    // draws circle
    two->Draw();    // draws rectangle
    three->Draw();  // draws circle

    ViewPause();
    // shut down the graphics system
    ShutdownGraphics();
}

/*
<Run of Program 12.3>

Area/perimeter of C and figures one-three:
C: 0.196349  1.570795
one: 0.785398  3.14159
two: 0.25  2
three: 0.196349  1.570795
Type <return> to view figures one and two and three.
*/
