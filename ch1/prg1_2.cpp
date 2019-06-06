#include <iostream.h>
#pragma hdrstop

#include "figures.h"
#include "dice.h"
#include "graphlib.h"

// toss two dice tossCount times. record number of 2's in
// tossTotal[2], number of 3's in tossTotal[3], and so forth
void SimulateDieToss(long tossTotal[], long tossCount)
{
    long tossEvent;
    int i;
    Dice D;
    
    // clear each element of sumcount
    for(i=2;i <= 12;i++)
        tossTotal[i] = 0;
        
    // toss the dice tossCount times
    for(tossEvent=1;tossEvent <= tossCount;tossEvent++)
    {
        D.Toss();               // toss the dice
        tossTotal[D.Total()]++; // increment count of die total
    }
}

// find maximum value in the n element array a
long Max(long a[], int n)
{
    long lmax = a[0];           // locally holds the maximum
    int i;
    
    for (i=1;i < n;i++)
        if (a[i] > lmax)
            lmax = a[i];
    return lmax;    
}

// Draw the two axes
void DrawAxes(void)
{
    const float vertspan = 3.0;
    
    Line VerticalAxis(Point(1.0,vertspan + .25),Point(1.0,.25));
    VerticalAxis.Draw();
    
    Line HorizontalAxis(Point(.75,vertspan),Point(7.0,vertspan));
    HorizontalAxis.Draw();
}

// draw the bar graph
void Plot(long tossTotal[])
{
    const float vertspan = 3.0, scaleHeight = 2.75;
    float x, rectHeight, dx;
    long maxTotal;
    int i;
    
    // find maximum value in tossTotal. look at index range 2-12.
    maxTotal = Max(&tossTotal[2],11);
    
    // now generate the rectangles
    dx = 6.0/23.0;
    x = 1.0 + dx;

    //  loop 11 times. in the loop,
    //      determine height of bar to draw at current position.
    //      create the Rectangle object of correct position,
    //      height and width. draw bar and move to next
    //      bar position. 
    for(i=2;i<= 12;i++)
    {
        rectHeight = (float(tossTotal[i])/maxTotal)*scaleHeight;
        Rectangle CurrRect(Point(x,vertspan-rectHeight),
                           Point(x+dx,vertspan));
        CurrRect.Draw();
        x += 2.0*dx;
    }
}

void main(void)
{
    long numTosses;
    long tossTotal[13];
    
    // prompt for the number of dice tosses in the simulation
    cout << "Enter the number of tosses: ";
    cin >> numTosses;
    
    SimulateDieToss(tossTotal, numTosses);  // toss the dice
    
    InitGraphics();         // initialize the graphics system
    
    DrawAxes();             // draw the axes
    Plot(tossTotal);        // plot the graph
    ViewPause();            // wait for key stroke or mouse down
        
    ShutdownGraphics();     // close down the graphics system
}

/*
<Run of Program 1.2>

Enter the number of tosses: 500000
*/
