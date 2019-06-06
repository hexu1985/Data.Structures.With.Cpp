#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#pragma hdrstop

#include "graphlib.h"
#include "shapelst.h"

void main(void)
{
    // listHeader is the header for the circular list of shapes
    NodeShape listHeader, *p, *nFig;
    
    // figures: 'c'(circle),'r'(rectangle),'t'(right triangle)
    char figType;
    
    // starting fill pattern is no fill
    int pat = 0;
    float x, y, radius, length, width, tb, th;
    
    // read figure data from stream fin
    ifstream fin;
    
    // open the file "figures" containing the figure data
    fin.open("figures",ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open 'figures'" << endl;
        exit(1);
    }
    
    // set p to point to list header
    p = &listHeader;
    
    // read until end of file and build linked list of figures
    while(!fin.eof())
    {
        // read figure type and base point
        fin >> figType;
        if (fin.eof())
            break;
        fin >> x >> y;
        
        // build the particular figure
        switch(figType)
        {
            case 'c':
                // read radius and insert circle
                fin >> radius;
                nFig = new CircleFigure(x,y,radius,pat);
                p->InsertAfter(nFig);
                break;
            case 'r':
                // read length and width and insert rectangle
                fin >> length >> width;
                nFig = new RectangleFigure(x,y,length,width,pat);
                p->InsertAfter(nFig);
                break;
            case 't':
                // read base and height and insert right triangle
                fin >> tb >> th;
                nFig = new RightTriangleFigure(x,y,tb,th,pat);
                p->InsertAfter(nFig);
                break;
        }
        
        // increment fill pattern. advance pointer to list rear
        pat = (pat+1) % 12;
        p = p->Next();
    }
    
    // initialize the graphics system
    InitGraphics();

    // start at 1st figure, chain the list and draw each one
    p = listHeader.Next();
    while (p != &listHeader)
    {
        p->Draw();
        p = p->Next();
    }
    
    // pause to view figures and shut down the graphics system
    ViewPause();
    ShutdownGraphics();
}

/*

<Run of Program 12.8>
    <graphic here>
    
*/
