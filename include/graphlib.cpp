//************************
//* Modified by DBSmith  *
//*   Fall, 1994         *
//************************

#include <graphics.h>
#include <conio.h>

const int scrwid = 10; //determines "unit" of length
//  for application to be 1/scrwid of
//  the actual screen width.

int xPixel(float x)
//*******************************************
//*  Computes x-pixels per unit of length   *
//*   as #pixels/screen width               *
//*  where screen width is a constant       *
//*******************************************
{ return (  ((getmaxx()+1) * x)/scrwid );
 }

int yPixel(float y)
//******************************************************
//* Computes y-pixels per unit of length (yppu)        *
//* as yppu = r * xppu where r is the aspect ratio     *
//* of the (x-pixel len)/(y-pixel length).             *
//*   r = xp/yp. yppu = 1/xp = (xp/yp)*(1/xp) = r*xppu *
//******************************************************
{
	 int xasp;     //x aspect
	 int yasp;     //y aspect
	 float yppu;   //y pixel per unit

	 getaspectratio(&xasp, &yasp); //ratio pixel width to height
	 yppu = float(xasp/yasp) * float((getmaxx()+1)/scrwid);
	 return (int ( y * yppu) );
}

void DrawPoint(float x, float y)
{ putpixel(xPixel(x),yPixel(y) , WHITE);
}

void DrawLine(float x1, float y1, float x2, float y2)
{  line(xPixel(x1),yPixel(y1),xPixel(x2),yPixel(y2)); }

void DrawRectangle(float left, float top, float right, float bottom)
{ rectangle( xPixel(left), yPixel(top), xPixel(right), yPixel(bottom));
  floodfill( (xPixel(left)+ xPixel(right))/2, (yPixel(top) + yPixel(bottom))/2,WHITE);
}

void DrawCircle(float x, float y, float r)
{ circle(xPixel(x),yPixel(y),xPixel(r));
  floodfill(xPixel(x), yPixel(y),WHITE);
}

void DrawPoly(float horz[], float vert[], float n)
{  int *polypoints;
	int i=0;

	polypoints = new int[2*n];
	for (int j=0; j<n; j++)
	 { polypoints[i] = xPixel(horz[j]);
		polypoints[i+1] = yPixel(vert[j]);
		i = i+ 2;
	 };

	 fillpoly(n,polypoints);
}

void SetFillStyle(int pattern)
{ setfillstyle(pattern,RED);
}

void InitGraphics(void)
{ int gdriver=DETECT, gmode;
  initgraph(&gdriver, &gmode, "c:\\bc45\\bgi");
  setbkcolor(LIGHTBLUE);
  cleardevice();
}

void ShutdownGraphics(void)
{ closegraph();
}

void ViewPause(void)
{getch();}

