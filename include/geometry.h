#ifndef GEOMETRIC_FIGURES
#define GEOMETRIC_FIGURES

// include the system dependent graphics library that
// initializes drawing to a screen and provides the routines
// to draw a rectangle, circle, line, and so forth 
#include "graphlib.h"

// a generic class that defines a point, a fill pattern and
// methods to access and change these parameters. the class
// is inherited by geometric figure classes that implement
// specific draw, area, and perimeter calculations 
class Shape
{
   protected:
      // horizontal and vertical pixel positions on the screen
      // data used by methods in a derived class
      float x, y;
      
      // fill pattern for the draw functions
      int fillpat;
   
   public:
      // constructor
      Shape(float h=0, float v=0, int fill=0);
      
      // methods to access x and y coordinates of base point
      float GetX(void) const;          // return x coordinate
      float GetY(void) const;          // return y coordinate
      void SetPoint(float h, float v); // change base point
      
      // methods to access the fill pattern for the shape
      int GetFill(void) const;         // return fill pattern
      void SetFill(int fill);          // change fill pattern
       
      // pure virtual functions. a derived class must define a
      // specific Area and Perimeter method
      virtual float Area(void) const = 0;
      virtual float Perimeter(void) const = 0;
      
      // virtual function that is called by a Draw method in a
      // derived class. initializes the fill pattern
      virtual void Draw(void) const;
};

// constructor. initialize the coordinates and fill pattern
Shape::Shape(float h, float v, int fill):
      x(h), y(v), fillpat(fill)
{}

float Shape::GetX(void) const
{
   return x;
}

float Shape::GetY(void) const
{
   return y;
}

int Shape::GetFill(void) const
{
   return fillpat;
}

void Shape::SetFill(int fill)
{
   fillpat = fill;
}

void Shape::SetPoint(float h, float v)
{
   x = h;
   y = v;
}

// set the fill style used when the shape is drawn
void Shape::Draw(void) const
{
   SetFillStyle(fillpat);  // call graphics system function
}

// constant data used by the area and circumference methods
const float PI = 3.14159;

// declaration of Circle class with base class Shape
class Circle: public Shape
{
   protected:
      // if Circle class becomes a base class, derived class
      // may have access to the radius
      float radius;
   
   public:
      // constructor. has parameters for center, radius and
      // fill pattern
      Circle(float h=0, float v=0, float r=0, int fill = 0);

      // radius access methods
      float GetRadius(void) const;
      void SetRadius(float r);

      // Circle Draw method; calls Draw in Shape class
      virtual void Draw(void) const;

      // measurement methods 
      virtual float Area(void) const;
      virtual float Perimeter(void) const;
};

// constructor. parameters h and v initialize base point
// in Shape class. point (h,v) represents center of the circle.
// parameter fill initializes fill pattern for Shape class.
// r is only parameter used exclusively by the Circle class.
// base object in Shape class is initialized by constructor
// Shape(h,v,fill) in the initializer list    
Circle::Circle(float h, float v, float r, int fill):
         Shape(h,v,fill), radius(r)
{}

// read the radius value; return value of private radius data 
float Circle::GetRadius(void) const
{
   return radius;
}

// change the radius value of the current object   
void Circle::SetRadius(float r)
{
   radius = r;          // assign r as the new radius
}

// draw the circle with center at (x,y) and given radius    
void Circle::Draw(void) const
{
   Shape::Draw();       // sets the fill pattern
   DrawCircle(x,y,radius);
}

// return circle area = PI * radius * radius       
float Circle::Area(void) const
{
   return PI * radius * radius;
}

// return circle  perimeter = 2 * PI * radius (circumference)
float Circle::Perimeter(void) const
{
   return 2.0 * PI * radius;
}


// ******************   Rectangle Class    ******************

// derived Rectangle Class; inherits the Shape class  
class Rectangle: public Shape
{
   protected:
      // protected data members that describe a rectangle
      float length, width;
   
   public:
      // constructor. has parameters for base point, length,
      // width, and fill pattern
      Rectangle(float h=0, float v=0, float l=0,
                float w=0, int fill = 0);
      
      // rectangle data access methods
      float GetLength(void) const;
      void SetLength(float l);
      float GetWidth(void) const;
      void SetWidth(float w);
      
      // override the virtual functions in the base class
      virtual void Draw(void) const;   // draw the rectangle
      virtual float Area(void) const;
      virtual float Perimeter(void) const;
};

Rectangle::Rectangle(float h,float v,float l,float w,int fill)
        :Shape(h,v,fill), length(l), width(w)
{}

float Rectangle::GetLength(void) const
{
   return length;
}
   
void Rectangle::SetLength(float l)
{
   length = l;
}
         
float Rectangle::GetWidth(void) const
{
   return width;
}
   
void Rectangle::SetWidth(float w)
{
   width = w;
}
         
void Rectangle::Draw(void) const
{
   Shape::Draw();    // set fill pattern
   // execute primitive function and draw the rectangle
   DrawRectangle(x,y,x+length,y+width);
}

float Rectangle::Area(void) const
{
   return length*width;
}

float Rectangle::Perimeter(void) const
{
   return 2.0 * (length + width);
}
   
#endif   // GEOMETRIC_FIGURES
