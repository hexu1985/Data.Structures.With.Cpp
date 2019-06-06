#ifndef GRAPHLIB
#define GRAPHLIB

void DrawPoint(float x, float y);
void DrawLine(float x1, float y1, float x2, float y2);
void DrawRectangle(float left, float top, float right, float bottom);
void DrawCircle(float x, float y, float r);
void DrawPoly(float horz[], float vert[], float n);

void SetFillStyle(int pattern);
void InitGraphics(void);        // Initialize the drawing surface
void ShutdownGraphics(void);    // Close the drawing surface
void ViewPause(void);           // Wait until a key or the mouse is pressed

#include "graphlib.cpp"

#endif // GRAPHLIB

