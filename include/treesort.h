#ifndef TREE_SORT
#define TREE_SORT

#include "bstree.h"
#include "treeiter.h"

// use a binary search tree to sort an array
template <class T>
void TreeSort(T arr[], int n)
{
   // binary search tree in which array data is placed
   BinSTree<T> sortTree;
   int i;
   
   // insert each array element into the search tree
   for (i=0;i < n;i++)
	  sortTree.Insert(arr[i]);

   // declare an inorder iterator for sortTree
   InorderIterator<T> treeSortIter(sortTree.GetRoot());
   
   // traverse tree inorder. assign each element back to arr
   i = 0;
   while(!treeSortIter.EndOfList())
   {
      arr[i++] = treeSortIter.Data();
      treeSortIter.Next();
   }
}

#endif   // TREE_SORT
