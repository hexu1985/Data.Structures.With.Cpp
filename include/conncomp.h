#ifndef CONNECTED_COMPONENTS
#define CONNECTED_COMPONENTS

#include "graph.h"
#include "seqlist2.h"

template <class T>
void PrintList(SeqList<T> &L)
{
	SeqListIterator<T>	liter(L);
	
	for (liter.Reset(); !liter.EndOfList(); liter.Next())
	    cout << liter.Data() << "  ";
}

template <class T>
int PathConnect (Graph<T> &G, T v, T w)
{
   SeqList<T> L;
   
   // find vertices connected to v
   L = G.DepthFirstSearch(v);
   // is w is in the list, return TRUE
   if (L.Find(w))
      return 1;
   else
      return 0;
}

template <class T>
void ConnectedComponent (Graph<T> &G)
{
   VertexIterator<T> viter(G);
   SeqList<T> markedList, scList, L;

   for (viter.Reset(); !viter.EndOfList(); viter.Next())
   {
      // loop checks each vertex viter.Data()
      if (!markedList.Find(viter.Data())) 
      
      // if not marked, put in a strong component    
      {
         scList.ClearList();

         // Get vertices connected to viter.Data()
         L = G.DepthFirstSearch(viter.Data());

         // Scan list to see if the node is connected
         // back to viter.Data()   
         SeqListIterator<T> liter(L);
         for (liter.Reset();!liter.EndOfList();liter.Next())
            if (PathConnect(G,liter.Data(),viter.Data()))
            {
               // insert vertices in the current strong component
               // and in markedList
               scList.Insert(liter.Data());
               markedList.Insert(liter.Data());
            }
         PrintList(scList);   // Print the strong component
         cout << endl;
      }
   }
}

#endif   // CONNECTED_COMPONENTS
