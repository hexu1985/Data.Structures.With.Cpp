// Ported to Visual C++ 5.0 Professional

#ifndef GRAPH_CLASS
#define GRAPH_CLASS

#include <iostream.h>
#include <fstream.h>

#include "stack.h"
#include "pqueue.h"
#include "queue.h"
#include "seqlist2.h"

const int MaxGraphSize = 25;

template <class T>
class VertexIterator;

template <class T> 
class Graph
{
   private:
      // key data including list of vertices, adjacency matrix
      // and current size (number of vertices) of the graph
      SeqList<T> vertexList;
      int edge [MaxGraphSize][MaxGraphSize];
      int graphsize;
      
      // methods to find vertex and identify position in list 
      int FindVertex(SeqList<T> &L, const T& vertex);
      int GetVertexPos(const T& vertex);
      
   public: 
      // constructor
      Graph(void);   
      
      // graph test methods               
      int GraphEmpty(void) const;
      int GraphFull(void) const;
      
      // data access methods
      int NumberOfVertices(void) const;
      int GetWeight(const T& vertex1, const T& vertex2);
      SeqList<T>& GetNeighbors(const T& vertex);
      
      // graph modification methods
      void InsertVertex(const T& vertex);
      void InsertEdge(const T& vertex1, const T& vertex2,
                      int weight);
      void DeleteVertex(const T& vertex);
      void DeleteEdge(const T& vertex1, const T& vertex2);
      
      // utility methods 
      void ReadGraph(char *filename);
      int MinimumPath(const T& sVertex, const T& eVertex);
      SeqList<T>& DepthFirstSearch(const T& beginVertex);
      SeqList<T>& BreadthFirstSearch(const T& beginVertex);
      
      // iterator used to scan the vertices
      friend class VertexIterator<T>;
};

// constructor initialize entries in the adjacency matrix
// to 0 and sets the graphsize to 0
template <class T>
Graph<T>::Graph(void)
{
   for (int i = 0; i < MaxGraphSize; i++)
      for (int j = 0; j < MaxGraphSize; j++)
         edge[i][j] = 0;
   graphsize = 0;
}
 
template <class T>
int Graph<T>::NumberOfVertices(void) const
{  
   return graphsize;
}
   
template <class T>
int Graph<T>::GraphEmpty(void) const
{  
   return graphsize == 0;
}

template <class T>
int Graph<T>::GetVertexPos(const T& vertex)
{   
   SeqListIterator<T> liter(vertexList);
   int pos = 0;
   
   while(!liter.EndOfList() && liter.Data() != vertex)
   {
      pos++;
      liter.Next();
   }
   
   if (liter.EndOfList())
   {
      cerr << "GetVertex: the vertex is not in the graph."
           << endl;
      pos = -1;
   }
   return pos;
}

template <class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2)
{
   int pos1=GetVertexPos(vertex1), pos2=GetVertexPos(vertex2);
   
   if (pos1 == -1 || pos2 == -1)
   {
      cerr << "GetWeight: a vertex is not in the graph."
           << endl;
      return -1;
   }

   return edge[pos1][pos2];
}

// return the list of all adjacent vertices
template <class T>
SeqList<T>& Graph<T>::GetNeighbors(const T& vertex)
{
   SeqList<T> *L;
   SeqListIterator<T> viter(vertexList);

   // allocate an SeqList
   L = new SeqList<T>;
   
   // look up pos in list to identify row in adjacency matrix
   int pos = GetVertexPos(vertex);
   
   // if vertex not in list of vertices, terminate
   if (pos == -1)
   {
      cerr << "GetNeighbors: the vertex is not in the graph."
           << endl;
      return *L;  // return empty list
   }

   // scan row of adjacency matrix and include all vertices
   // having a non-zero weighted edge from vertex
   for (int i = 0; i < graphsize; i++)
   {
      if (edge[pos][i] > 0)
         L->Insert(viter.Data());
      viter.Next();
   }
   return *L;
}

template <class T>
void Graph<T>::InsertVertex(const T& vertex)
{
   if (graphsize+1 > MaxGraphSize)
   {  
      cerr << "Graph is full" << endl;
      exit (1);      
   }
   vertexList.Insert(vertex);
   graphsize++;
}

template <class T>
void Graph<T>::InsertEdge(const T& vertex1,
                          const T& vertex2, int weight)
{
   int pos1=GetVertexPos(vertex1), pos2=GetVertexPos(vertex2);
   
   if (pos1 == -1 || pos2 == -1)
   {
      cerr << "InsertEdge: a vertex is not in the graph."
           << endl;
      return;
   }
   
   edge[pos1][pos2] = weight;
}

// delete a vertex from vertex list and update the adjacency 
// matrix to remove all edges linked to the vertex. 
template <class T>
void Graph<T>::DeleteVertex(const T& vertex)
{
   // get the position in the vertex list
   int pos = GetVertexPos(vertex);
   int row, col;
   
   // if vertex is not present, terminate the program
   if (pos == -1)
   {
      cerr << "DeleteVertex: a vertex is not in the graph."
           << endl;
      return;
   }

   // delete the vertex and decrement graphsize
   vertexList.Delete(vertex);
   graphsize--;

   // the adjacency matrix is partitioned into three regions
   for (row = 0; row < pos; row++)              // region I
      for (col = pos + 1;col < graphsize;col++)
         edge[row][col-1] = edge[row][col];

   for (row = pos+1;row < graphsize;row++)      // region II
      for (col = pos + 1; col < graphsize; col++)
         edge[row-1][col-1] = edge[row][col];

   for (row = pos+1;row < graphsize;row++)      // region III
      for (col = 0; col < pos; col++)
         edge[row-1][col] = edge[row][col];
}

template <class T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2)
{
   int pos1=GetVertexPos(vertex1), pos2=GetVertexPos(vertex2);

   if (pos1 == -1 || pos2 == -1)
   {
      cerr << "DeleteEdge: a vertex is not in the graph."
           << endl;
      return;
   }
   edge[pos1][pos2] = 0;
}

template <class T>
int Graph<T>::FindVertex(SeqList<T> &L, const T& vertex)
{
   SeqListIterator<T> iter(L);
   int ret = 0;
   
   while(!iter.EndOfList())
   {
      if (iter.Data() == vertex)
      {
         ret = 1;
         break;
      }
      iter.Next();
   }
   return ret;
}

// from a starting vertex, return depth first scanning list
template <class T>
SeqList<T> & Graph<T>::DepthFirstSearch(const T& beginVertex)
{
   // stack to temporarily hold waiting vertices
   Stack<T> S;

   // L is list of nodes on the scan; adjL holds the
   // neighbors of the current vertex. L is created
   // in dynamic memory so a reference to it can be
   // returned
   SeqList<T> *L, adjL;
   // iteradjL used to traverse neighbor lists
   SeqListIterator<T> iteradjL(adjL);
   T vertex;
   
   // initialize return list; push starting vertex on stack
   L = new SeqList<T>;
   S.Push(beginVertex);

   // scan continues until the stack is empty
   while (!S.StackEmpty())
   {
      // pop next vertex
      vertex = S.Pop();
      // check if it is already in L      
      if (!FindVertex(*L,vertex))
      {
         // if not, put it in L and get all adjacent vertices
         (*L).Insert(vertex);
         adjL = GetNeighbors(vertex);
         // set iterator to current adjL
         iteradjL.SetList(adjL);
         
         // scan list of neighbors; put on stack if not in L
         for(iteradjL.Reset();!iteradjL.EndOfList();iteradjL.Next()) 
            if (!FindVertex(*L,iteradjL.Data()))
               S.Push(iteradjL.Data());
      }
   }
   // return depth first scan list.
   return *L;  // return list
}
   
template <class T>
SeqList<T>& Graph<T>::BreadthFirstSearch(const T& beginVertex)
{
   Queue<T> Q;
   SeqList<T> *L, adjL;
   SeqListIterator<T> iteradjL(adjL);
   T vertex;
   
   L = new SeqList<T>;
   Q.QInsert(beginVertex);   // initialize the queue
   
   while (!Q.QEmpty())
   {
      // remove a vertex from the queue
      vertex = Q.QDelete();
      
      // if vertex is not in L, add it
      if (!FindVertex(*L,vertex))
      {
         (*L).Insert(vertex);
         
         // get list of neighbors of vertex
         adjL = GetNeighbors(vertex);
         iteradjL.SetList(adjL);
         
         // insert all neighbors of vertex into the queue
         // if they are not already there
         for(iteradjL.Reset();!iteradjL.EndOfList();iteradjL.Next())
         {
            if (!FindVertex(*L,iteradjL.Data()))
               Q.QInsert(iteradjL.Data());
         }
      }
   }
   return *L;
}

template <class T> 
struct PathInfo
{
   T startV, endV;
   int cost;
};
   
template <class T>
int operator <= (const PathInfo<T>& a, const PathInfo<T>& b)
{
   return a.cost <= b.cost;
}

template <class T>
int Graph<T>::MinimumPath(const T& sVertex, const T& eVertex)
{
   // priority queue into which info about path cost
   // from sVertex is placed
   PQueue< PathInfo<T> > PQ(MaxGraphSize);
   // used when inserting PathInfo entries
   // into the priority queue or deleting entries
   PathInfo<T> pathData;
   // L holds list of all vertices reachable from sVertex
   // whose cost we have considered. adjL is neighbor 
   // list of vertices we are visiting. adjLiter is used
   // to traverse adjL
   SeqList<T> L, adjL;
   SeqListIterator<T> adjLiter(adjL);
   T sv, ev;
   int mincost;

   // formulate initial priority queue entry
   pathData.startV = sVertex; 
   pathData.endV = sVertex;
   // cost from sVertex to sVertex is 0
   pathData.cost = 0;
   PQ.PQInsert(pathData);

   // process vertices until we find a minimum path to
   // eVertex or the priority queue is empty
   while (!PQ.PQEmpty())
   {
      // delete a priority queue entry, and record its
      // ending vertex and cost from sVertex.
      pathData = PQ.PQDelete();
      ev = pathData.endV;
      mincost = pathData.cost;
      
      // if we are at eVertex, we have found the minimum
      // path from sVertex to eVertex
      if (ev == eVertex)
         break;
         
      // if ending vertex is already in L, do not consider
      // it again
      if (!FindVertex(L,ev))
      {
         // insert ev into L
         L.Insert(ev);
         // find all neighbors of the current vertex ev. for
         // each neighbor that is not in L, generate an entry
         // and insert it into priority queue with starting
         // vertex ev
         sv = ev;
         adjL = GetNeighbors(sv);
         // adjLiter traverses new list adjL
         adjLiter.SetList(adjL);
         for(adjLiter.Reset();!adjLiter.EndOfList();
                              adjLiter.Next())
         {
            ev = adjLiter.Data();
            if (!FindVertex(L,ev))
            {
               // create new entry for the priority queue
               pathData.startV = sv;
               pathData.endV = ev;
               // cost is current minimum cost plus the cost
               // of going from sv to ev
               pathData.cost = mincost+GetWeight(sv,ev);
               PQ.PQInsert(pathData);
            }
         }
      }
   }

   // return success or failure
   if (ev == eVertex)
      return mincost;
   else
      return -1;
}

template <class T>
void Graph<T>::ReadGraph(char *filename)
{
   int i, nvertices, nedges;
   T S1, S2;
   int weight;
   ifstream f;

   f.open(filename, ios::in | ios::nocreate);
   if(!f)
   {
      cerr << "Cannot open " << filename << endl;
      exit(1);
   }

   f >> nvertices;
   for (i = 0; i < nvertices; i++)
   {
      f >> S1;
      InsertVertex(S1);
   }

   f >> nedges;
   for (i = 0; i < nedges; i++)
   {
      f >> S1;
      f >> S2;
      f >> weight;
      InsertEdge(S1,S2, weight);
   }
   f.close();
}

template <class T>
class VertexIterator: public SeqListIterator<T>
{
   public:
      VertexIterator(Graph<T>& G);
};

template <class T>
VertexIterator<T>::VertexIterator(Graph<T>& G):
   SeqListIterator<T> (G.vertexList)
{}

#endif   // GRAPH_CLASS
