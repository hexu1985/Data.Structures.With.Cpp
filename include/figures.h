#include "graphlib.h"

class Point
{
    private:
        float  x, y;                // horizontal and vertical positions

    public:
        Point(float h, float v);    // assign h to x and v to y
        float GetX(void) const;     // return x (horizontal) coordinate                          
        float GetY(void) const;     // return y (vertical) coordinate
        void Draw(void) const;      // draw a dot at (X,Y)  
};

Point::Point(float h, float v) : x(h), y(v)
{}

float Point::GetX(void) const
{
    return x;
}

float Point::GetY(void) const
{
    return y;
}

void Point::Draw(void) const
{
    DrawPoint(x,y); // Draw the point
}

class Line
{
    private:
        Point  p1, p2;              // two end points of the line segment

    public:
        Line(Point a, Point b);     // assign a to p1 and b to p2
        void Draw(void) const;      // draw the line segment    
};

Line::Line(Point a, Point b) : p1(a), p2(b)
{}

void Line::Draw(void) const
{
    DrawLine(p1.GetX(),p1.GetY(),p2.GetX(), p2.GetY()); // Draw line
}

class Rectangle
{
    private:
        Point  ul, lr;                  // extreme corner points

    public:
        Rectangle(Point a, Point b);    //  assign a to UL and b to LR

        void Draw(void) const;          // draw the rectangle   
};

Rectangle::Rectangle(Point a, Point b) : ul(a), lr(b)
{}

void Rectangle::Draw(void) const
{
    DrawRectangle(ul.GetX(),ul.GetY(),  lr.GetX(),lr.GetY());
}
