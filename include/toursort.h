#ifndef TOURNAMENT_SORT
#define TOURNAMENT_SORT

template <class T>
struct DataNode
{
   // data value, index in the tree, boolean flag
   T  data;
   int index;
   int active;
};

// overloaded '<' operator; compares the data field
template <class T>
int operator < (const DataNode<T> &x, const DataNode<T> &y)
{
   if (x.active && y.active)
      return x.data < y.data;
   else 
      return 1;
} 

// finds smallest power of 2 that is greater than n 
int PowerOfTwo (int n)
{
   int total = 2;

   while (total < n)
      total *=2;
   return total;
}

// the parameter i is the starting index of the current
// smallest element in the list (tournament winner)
template <class T>
void UpdateTree(DataNode<T> *tree, int i)
{
   int j;
   
   // identify competitor of winner i. allow that competitor
   // to re-enter tournament by assigning it to parent node
   if (i % 2 == 0)
      tree[(i-1)/2] = tree[i-1];   // competitor is left node
   else
      tree[(i-1)/2] = tree[i + 1]; // competitor is right node
   
   // with the winner out of the tournament (made inactive),
   // replay those matches that involved this inactive player
   i = (i-1)/2;
   while (i > 0)
   {
      // at position i, is competitor a left or right node?
      if (i % 2 == 0)
         j = i-1;
      else
         j = i + 1;
      // see if your competitor is inactive (no match)
      if (!tree[i].active || !tree[j].active)
         if (tree[i].active)
            tree[(i-1)/2] = tree[i];
         else
            tree[(i-1)/2] = tree[j];
      // we have a competition. winner assigned to parent
      else
         if (tree[i] < tree[j])
            tree[(i-1)/2] = tree[i];
         else
            tree[(i-1)/2] = tree[j];
      // move to next level of competition (parent level)
      i = (i-1)/2;
   }
   // tournament with new competitor is over. next smallest
   // value is available in the root
}

// set up array-based tree, copy elements of array a to
// new tree; sort elements and copy their value back to 
// the array
template <class T>   
void TournamentSort (T a[], int n)
{
   // tree is the root of the array-based tree
   DataNode<T> *tree;
   DataNode<T> item;
   
   // minimum power of 2 that is >= n
   int bottomRowSize;

   // number of nodes in the complete tree
   // whose last row has bottomRowSize entries
   int treesize;

   // starting index of the bottom row
   int loadindex;
   int i, j;
   
   // call PowerOfTwo to determine the needed size of 
   // the bottom row of the tree.
   bottomRowSize = PowerOfTwo(n);
   
   // compute the size of the tree and dynamically
   // allocate its nodes
   treesize = 2 * bottomRowSize - 1;
   loadindex = bottomRowSize-1;
   tree = new DataNode<T>[treesize];
   
   // copy the array a to the tree of DataNode objects
   j = 0;
   for (i = loadindex; i < treesize; i++)
   {
      item.index = i;
      if (j < n)
      {
         item.active = 1;        // set flag to active
         item.data = a[j++];
      }
      else
         item.active = 0;         
      tree[i] = item;            // assign object to tree
   }

   // make initial set of comparisons to find smallest item
   i = loadindex;
   while (i > 0)
   {
       j = i;
       while (j < 2*i)   // process pairs of competitors
       { 
         // have a match. compare value tree[j] with its
         // competitor tree[j+1]. assign the winner to
         // the parent position
         if (!tree[j+1].active || tree[j] < tree[j+1])
            tree[(j-1)/2] = tree[j];
         else
            tree[(j-1)/2] = tree[j + 1];
         j += 2;         // go to next pair of competitors
       }
       // move up to the next level for competition among
       // the winners of the previous matches
       i = (i-1)/2;
   }
   
   // handle other n-1 elements. copy winner from the root
   // to the array. make the winner inactive. update tree
   // by allowing the winner's competitor to re-enter the
   // tournamemt 
   for (i = 0; i < n-1; i++)
   {
      a[i] = tree[0].data;
      tree[tree[0].index].active = 0;
      UpdateTree(tree,tree[0].index);
   }
   // this copies the largest value to the array
   a[n-1] = tree[0].data;
}

#endif   // TOURNAMENT_SORT
