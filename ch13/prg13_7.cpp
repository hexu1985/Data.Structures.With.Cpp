#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "graph.h"

template <class T>
void Warshall(Graph<T>& G)
{
	VertexIterator<T> vi(G), vj(G);
   
	int i, j, k;
	int WSM[MaxGraphSize][MaxGraphSize];  // Warshall matrix
	int n = G.NumberOfVertices();
   
	// create the initial matrix. WSM[i][i] = 1. WSM[i][j], i != j, is 1
	// if there is a vertex from Vi to Vj; otherwise WSM[i][j] = 0.
	for(vi.Reset(),i=0;!vi.EndOfList();vi.Next(),i++)
		for(vj.Reset(),j= 0;!vj.EndOfList();vj.Next(), j++)
			if (i == j)
				WSM[i][i] = 1; 
			else
				WSM[i][j] = G.GetWeight(vi.Data(),vj.Data()) != 0 ? 1 : 0;
   
	// look at all triples. assign 1 to WSM when there is a triple
	// vi - vk - vj connecting vi and vj.
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				WSM[i][j] = WSM[i][j] || WSM[i][k] && WSM[k][j];
   
	// print each vertex and its row of the Warshall
	// matrix
	for (vi.Reset(), i=0;!vi.EndOfList();vi.Next(), i++)
	{
		cout << vi.Data() << ":  ";
		for (j = 0; j < n; j++)
			cout << WSM[i][j] << "  ";
		cout << endl;
	}
}

void main(void)
{
	Graph<char> G;
	
	G.ReadGraph("warshall.dat");
	
	cout << "The reachability matrix is:" << endl;
	Warshall(G);
}

/*
<Run of Program 13.7>

The reachability matrix is:
A:  1  1  1  0  1
B:  0  1  1  0  1
C:  0  0  1  0  0
D:  1  1  1  1  1
E:  0  0  1  0  1
*/
