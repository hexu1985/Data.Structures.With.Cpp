#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "graph.h"
#include "conncomp.h"

void main(void)
{
	Graph<char> G;

	G.ReadGraph("sctest.dat");

	cout << "Strong Components:" << endl;
	ConnectedComponent(G);
} 

/*
<Run of Program 13.5>

Strong Components:
A  B  C
D  G  F
E
*/
