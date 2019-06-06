#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "strclass.h"
// include the graph class with the MinimumPath method
#include "graph.h"

void main(void)
{
    // vertices are strings (airline cities)
    Graph<String>   G;
    String  S;
    
    // input the vertices for transportation graph
    G.ReadGraph("airline.dat"); 
    
    // prompt for the departure city
    cout << "Give the minimum distance when departing from ";
    cin >> S;

    // using a graph iterator, scan the list of cities and
    // determine the minumum distance from the departure city
    VertexIterator<String>  Viter(G);
    for (Viter.Reset(); !Viter.EndOfList(); Viter.Next())
    	cout << "Minimum distance from " << S << " to " <<
    		Viter.Data() << " is " << 
    		G.MinimumPath(S,Viter.Data()) << endl;
}
/*

<Run #1 of Program 13.6>

Give the minimum distance when departing from SaltLakeCity
Minimum distance from SaltLakeCity to SaltLakeCity is 0
Minimum distance from SaltLakeCity to Albuquerque is 604
Minimum distance from SaltLakeCity to Phoenix is 648
Minimum distance from SaltLakeCity to SanFrancisco is 752
Minimum distance from SaltLakeCity to SanDiego is 1003

<Run #2 of Program 13.6>

Give the minimum distance when departing from SanFrancisco
Minimum distance from SanFrancisco to SaltLakeCity is 752
Minimum distance from SanFrancisco to Alburqueque is 1195
Minimum distance from SanFrancisco to Phoenix is 763
Minimum distance from SanFrancisco to SanFrancisco is 0
Minimum distance from SanFrancisco to SanDiego is 504
*/
