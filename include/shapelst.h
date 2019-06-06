#ifndef GEOMETRIC_FIGURES
#define GEOMETRIC_FIGURES

#include "graphlib.h"

// base class NodeShape
class NodeShape
{
   protected:
      // coordinates of base point, fill pattern and pointer
      // to the next node
      float x, y;
      int fillpat;
      NodeShape *next;
   
   public:
      // constructor
      NodeShape(float h = 0, float v = 0, int fill = 0);
      
      // virtual drawing function
      virtual void Draw(void) const;
      
      // list handling methods
      void InsertAfter(NodeShape *p);
      NodeShape *DeleteAfter(void);
      NodeShape *Next(void);
};

// constructor. initialize base point, fill pattern, and set
// node to point to itself
NodeShape::NodeShape(float h, float v, int fill):
          x(h), y(v), fillpat(fill)
{
   next = this;
}

// set system fill pattern
void NodeShape::Draw(void) const
{
   SetFillStyle(fillpat);
}

// insert node p after the current node
void NodeShape::InsertAfter(NodeShape *p)
{
   // p points to successor of current node, and current node
   // points to p
   p->next = next;
   next = p;
}

// unlink node following current one and return its address
NodeShape *NodeShape::DeleteAfter(void)
{
   // save address of node to be deleted
   NodeShape *tempPtr = next;
   
   // if next is the address of current object (this), we are
   // pointing to ourself, so we don't delete! return NULL
   if (next == this)
      return NULL;
      
   // current node points to successor of tempPtr.
   next = tempPtr->next;
   
   // return the pointer to the unlinked node
   return tempPtr;
}

// return pointer to the next node
NodeShape *NodeShape::Next(void)
{
   return next;
}

// CircleFigure is derived from NodeShape base class
class CircleFigure: public NodeShape
{
   protected:
      // radius of the circle
      float radius;
   
   public:
      // constructor
      CircleFigure(float h, float v, float r, int fill);
      
      // virtual drawing function. draws a circle
      virtual void Draw(void) const;
};

// constructor. initialize base class and radius
CircleFigure::CircleFigure(float h,float v,float r,int fill):
         NodeShape(h,v,fill), radius(r)
{}

// set fill pattern by calling base class Draw and draw circle
void CircleFigure::Draw(void) const
{
   NodeShape::Draw();
   DrawCircle(x,y,radius);
}

// RectangleFigure is derived from NodeShape base class
class RectangleFigure: public NodeShape
{
   protected:
      // length and width of the rectangle
      float length, width;
   
   public:
      // constructor
      RectangleFigure(float h, float v, float l,
                      float w, int fill);
      
      // virtual drawing function. draws a rectangle
      virtual void Draw(void) const;
};

// constructor. initialize base class and length/width
RectangleFigure::RectangleFigure(float h, float v, float l,
                                 float w, int fill):
         NodeShape(h,v,fill), length(l), width(w)
{}

// set fill pattern by calling base class Draw. draw rectangle
void RectangleFigure::Draw(void) const
{
   NodeShape::Draw();
   // execute primitive function and draw the rectangle
   DrawRectangle(x,y,x+length,y+width);
}

// RightTriangleFigure is derived from NodeShape base class
class RightTriangleFigure: public NodeShape
{
   protected:
      // length of the base and the height
      float base,height;
   
   public:
      // constructor
      RightTriangleFigure(float h, float v, float b,
                          float ht,int fill);
      
      // virtual drawing function. draws a right triangle
      virtual void Draw(void) const;
};

// constructor. initialize base class, base/height of triangle
RightTriangleFigure::RightTriangleFigure(float h, float v,
                                   float b,float ht,int fill):
      NodeShape(h,v,fill), base(b),height(ht)
{}

// set fill pattern by calling base class Draw. draw triangle
void RightTriangleFigure::Draw(void) const
{
   // coordinates of the three points of the right triangle
   float horz[3] = {x,x+base,x+base},
         vert[3] = {y,y,y-height};
         
   NodeShape::Draw();
   // draw polygon with three vertices (horz[0],vert[0]), etc.
   DrawPoly(horz,vert,3);
}
   
#endif   // GEOMETRIC_FIGURES
