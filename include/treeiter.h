#ifndef TREE_ITERATOR
#define TREE_ITERATOR

#include "treenode.h"
#include "iterator.h"
#include "stack.h"

#ifndef NULL
const int NULL = 0;
#endif   // NULL

// Inorder iterator for binary tree; uses Iterator base class
template <class T>
class InorderIterator: public Iterator<T>
{
   private:
      // we maintain a stack of TreeNode addresses
      Stack< TreeNode<T> * > S;
      // tree root and current node
      TreeNode<T> *root, *current;
      
      // traverse a left path. used by Next
      TreeNode<T> *GoFarLeft(TreeNode<T> *t);
   public:
	  // constructor
      InorderIterator(TreeNode<T> *tree);

	  // implementation of basic traversal operations
      virtual void Next(void);
      virtual void Reset(void);
      virtual T& Data(void);
      
	  // assign new tree list to iterator
      void SetTree(TreeNode<T> *tree);
};

// return address of last node on the left branch from t,
// stacking node addresses as we go
template <class T>
TreeNode<T> *InorderIterator<T>::GoFarLeft(TreeNode<T> *t)
{
   // if t is NULL, return NULL
   if (t == NULL)
      return NULL;
      
   // go as far left in the tree t as possible, stacking each
   // node address on S until a node is found with a NULL
   // left pointer. return a pointer to that node
   while (t->Left() != NULL)
   {
      S.Push(t);
      t = t->Left();
   }
   return t;
}

// initialize iterationComplete. base class sets it to 0, but
// the tree may be empty. first node in traversal is farthest
// node left.
template <class T>
InorderIterator<T>::InorderIterator(TreeNode<T> *tree):
      Iterator<T>(), root(tree)
{
   iterationComplete = (root == NULL);
   current = GoFarLeft(root);
}

template <class T>
void InorderIterator<T>::Next(void)
{  
   // error if we have already visited all the nodes
   if (iterationComplete)
   {
      cerr << "Next: iterator has passed the end of list!"
          << endl;
      exit(1);
   }
   
   // we have visited node current
   // if have a right subtree, move right and go far left,
   // stacking up nodes on the left subtree
   if (current->Right() != NULL)
      current = GoFarLeft(current->Right());
      
   // no right subtree, but there are other nodes we have
   // stacked we must process. pop stack into current
   else if (!S.StackEmpty())     // move up the tree
      current = S.Pop();

   // no right branch of current node and no stacked nodes.
   // the traversal is complete
   else
      iterationComplete = 1;
}

// reset the traversal to the first tree node
template <class T>
void InorderIterator<T>::Reset(void)
{
   // clear out the stack of node addresses
   S.ClearStack();
   
   // reassign iterationComplete and current the address of
   // the first node in the inorder scan
   iterationComplete = (root == NULL);
   current = GoFarLeft(root); // go back to 1st node inorder
}

// return current data value
template <class T>
T& InorderIterator<T>::Data(void)
{
   // error if tree empty or we have completed traversal
   if (root == NULL || iterationComplete)
   {
      cerr << "Data: invalid reference!" << endl;
      exit(1);
   }
   return current->data;
}

template <class T>
void InorderIterator<T>::SetTree(TreeNode<T> *tree)
{
   // clear out the stack of node addresses
   S.ClearStack();
   
   // assign new tree root. initialize iterationComplete.
   // assign current the address of first node in the scan
   root = tree;
   iterationComplete = (root == NULL);
   current = GoFarLeft(root); // go to 1st node inorder
}

#endif   // TREE_ITERATOR
