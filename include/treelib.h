#ifndef TREE_LIBRARY_FUNCTIONS
#define TREE_LIBRARY_FUNCTIONS

#include <iostream.h>
#include <stdlib.h>

#include "treenode.h"


#ifndef NULL
const int NULL = 0;
#endif   // NULL

// create TreeNode object with pointer fields lptr and rptr
// the pointers have default value NULL. 
template <class T>
TreeNode<T> *GetTreeNode(T item,TreeNode<T> *lptr = NULL,
                         TreeNode<T> *rptr = NULL)
{
   TreeNode<T> *p;

   // call new to allocated the new node
   // pass parameters lptr and rptr to the function
   p = new TreeNode<T> (item, lptr, rptr);
   
   // if insufficient memory, exit with an error message 
   if (p == NULL)
   {
      cerr << "Memory allocation failure!\n";
      exit(1);
   }
   
   // return the pointer to the system generated memory
   return p;
}

// deallocate dynamic memory associated with the node
template <class T>
void FreeTreeNode(TreeNode<T> *p)
{
   delete p;
}

// using GetTreeNode, dynamically create three binary trees
// starting at the leaf nodes and stopping with the root node
// n is a parameter that selects from tree 0 - tree 2 
void MakeCharTree(TreeNode<char>* &root, int n)
{
   // 9 TreeNode pointers; points to the 9 items in the tree 
   TreeNode<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;

   // parameter n specifies a tree in the range 0 - 2
   switch(n)
   {
      // nodes D and E leaf nodes ; A is root node
      case 0:
         d = GetTreeNode('D');
         e = GetTreeNode('E');
         b = GetTreeNode('B',(TreeNode<char> *)NULL, d);
         c = GetTreeNode('C',e, (TreeNode<char> *)NULL);
         a = GetTreeNode('A',b, c);
         root = a;
         break;
         
      // nodes E, G, H, and I leaf nodes ; A is root node
      case 1:
         g = GetTreeNode('G');
         h = GetTreeNode('H');
         i = GetTreeNode('I');
         d = GetTreeNode('D');
         e = GetTreeNode('E',g, (TreeNode<char> *)NULL);
         f = GetTreeNode('F',h, i);
         b = GetTreeNode('B',d, e);
         c = GetTreeNode('C',(TreeNode<char> *)NULL, f);
         a = GetTreeNode('A',b, c);
         root = a;
         break;
         
      // nodes F, G, H, and I leaf nodes ; A is root node
       case 2:
         g = GetTreeNode('G');
         h = GetTreeNode('H');
         i = GetTreeNode('I');
         d = GetTreeNode('D',(TreeNode<char> *)NULL, g);
         e = GetTreeNode('E',h, i);
         f = GetTreeNode('F');
         b = GetTreeNode('B',d, (TreeNode<char> *)NULL);
         c = GetTreeNode('C',e, f);
         a = GetTreeNode('A',b, c);
         root = a;
         break;
   }
}

// the function uses a postorder scan. a visit 
// tests whether the node is a leaf node
template <class T>
void CountLeaf (TreeNode<T> *t, int& count)
{
   // use posorder descent
   if (t != NULL) 
   {
      CountLeaf(t->Left(), count);  // descend left
      CountLeaf(t->Right(), count); // descend right

      // check if t is a leaf node (no descendants) 
      // if so increment the variable count
      if (t->Left() == NULL && t->Right() == NULL)
         count++;
   }
}


// the function uses a postorder scan. it computes the
// depth of the left and right subtrees of a node and
// returns the depth of the tree as
// 1+ max(depthLeft,depthRight). the depth
// of an empty tree is -1
template <class T>
int Depth (TreeNode<T> *t)
{
   int depthLeft, depthRight, depthval;

   if (t == NULL) 
	  depthval = -1;
   else
   {
      depthLeft= Depth(t->Left());
	  depthRight= Depth(t->Right());
      depthval = 1 +
		 (depthLeft> depthRight?depthLeft:depthRight);
   }
   return depthval;
}

// create duplicate of tree t; return the new root 
template <class T>
TreeNode<T> *CopyTree(TreeNode<T> *t)
{  

   // variable newnode points at each new node that is 
   // created by a call to GetTreeNode and later attached to 
   // the new tree. newlptr and newrptr point to the child of 
   // newnode and are passed as parameters to GetTreeNode
   TreeNode<T> *newlptr, *newrptr, *newnode;
   
   // stop the recursive scan when we arrive at empty tree
   if (t == NULL)
      return NULL;
      
   // CopyTree builds a new tree by scanning the nodes of t.
   // At each node in t, CopyTree checks for a left child. if
   // present it makes a copy of left child or returns NULL.   
   // The algorithm similarly checks for a right child. 
   // CopyTree then builds a copy of node using GetTreeNode 
   // and appends copy of left and right children to node. 
   if (t->Left() != NULL) 
      newlptr = CopyTree(t->Left());
   else
      newlptr = NULL;
 
   if (t->Right() != NULL) 
      newrptr = CopyTree(t->Right());
   else
      newrptr = NULL;
 
   
   // build new tree from the bottom up by building the two 
   // children and then building the parent. 
   newnode = GetTreeNode(t->data, newlptr, newrptr);
   
   // return a pointer to the newly created node
   return newnode;
}

// use the postorder scan algorithm to traverse the nodes in
// the tree and delete each node as the visit operation.
template <class T>
void DeleteTree(TreeNode<T> *t)
{
   if (t != NULL)
   {
      DeleteTree(t->Left());
      DeleteTree(t->Right());
      FreeTreeNode(t);
   }
}

// call the function DeleteTree to deallocate the nodes. then
// set the root pointer back to NULL
template <class T>
void ClearTree(TreeNode<T> * &t)
{
   DeleteTree(t);
   t = NULL;      // root now NULL
}

#endif   // TREE_LIBRARY_FUNCTIONS
