#ifndef AVLTREE_CLASS
#define AVLTREE_CLASS

#include <iostream.h>
#include <stdlib.h>

#include "bstree.h"

// ***********************************************************
// **********     AVLTreeNode class 		 *******************
// ***********************************************************

template <class T>
class AVLTree;

// inherits the TreeNode class
template <class T>
class AVLTreeNode: public TreeNode<T>
{
   private:
      // additional data member needed by AVLTreeNode
      int balanceFactor;
      // used by AVLTree class methods to allow assignment
      // to a TreeNode pointer without casting
      AVLTreeNode<T>* & Left(void);
      AVLTreeNode<T>* & Right(void);

   public:
      // constructor
      AVLTreeNode (const T& item, AVLTreeNode<T> *lptr = NULL,
                   AVLTreeNode<T> *rptr = NULL, int balfac = 0);
         
      // methods that return left/right TreeNode pointers as 
      // AVLTreeNode pointers; handles casting for the client
      AVLTreeNode<T>* Left(void) const;
      AVLTreeNode<T>* Right(void) const;

      // method to access new data field
      int GetBalanceFactor(void);
   
      // AVLTree methods needs access to left and right
      friend class AVLTree<T>;
};

// return a reference to left after casting it to an
// AVLTreeNode pointer. use to change left
template <class T>
AVLTreeNode<T>* & AVLTreeNode<T>::Left(void)
{
   return (AVLTreeNode<T> *)left;
}

// return a reference to right after casting it to an
// AVLTreeNode pointer. use to change right
template <class T>
AVLTreeNode<T>* & AVLTreeNode<T>::Right(void)
{
   return (AVLTreeNode<T> *)right;
}


// constructor; initialize balanceFactor and the base class.
// default pointer values NULL initialize node as a leaf node
template <class T>
AVLTreeNode<T>::AVLTreeNode (const T& item,
      AVLTreeNode<T> *lptr, AVLTreeNode<T> *rptr, int balfac):
   TreeNode<T>(item,lptr,rptr), balanceFactor(balfac)
{}

// return left after casting it to an AVLTreeNode pointer
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::Left(void) const
{
   return (AVLTreeNode<T> *)left;
}

// return right after casting it to an AVLTreeNode pointer
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::Right(void) const
{
   return (AVLTreeNode<T> *)right;
}

template <class T>
int AVLTreeNode<T>::GetBalanceFactor(void)
{
   return balanceFactor;
}

// *************  AVLTree class  *************************
// *******************************************************

// constants to indicate the balance factor of a node
const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

// derived search tree class
template <class T>
class AVLTree: public BinSTree<T>
{
   private:
   
      // memory allocation
      AVLTreeNode<T> *GetAVLTreeNode(const T& item,
               AVLTreeNode<T> *lptr,AVLTreeNode<T> *rptr);
      
      // used by copy constructor and assignment operator
      AVLTreeNode<T> *CopyTree(AVLTreeNode<T> *t);
      
      // used by Insert and Delete method to re-establish 
      // the AVL conditions after a node is added or deleted
      // from a subtree
      void SingleRotateLeft (AVLTreeNode<T>* &p);
      void SingleRotateRight (AVLTreeNode<T>* &p);
      void DoubleRotateLeft (AVLTreeNode<T>* &p);
      void DoubleRotateRight (AVLTreeNode<T>* &p);
      void UpdateLeftTree (AVLTreeNode<T>* &tree,
                      int &reviseBalanceFactor);
      void UpdateRightTree (AVLTreeNode<T>* &tree,
                        int &reviseBalanceFactor);
      
      // class specific versions of the general Insert and
      // Delete methods
      void AVLInsert(AVLTreeNode<T>* &tree,
            AVLTreeNode<T>* newNode, int &reviseBalanceFactor);
      void AVLDelete(AVLTreeNode<T>* &tree,
            AVLTreeNode<T>* newNode, int &reviseBalanceFactor);
      
   public:
      // constructors, destructor
      AVLTree(void);
      AVLTree(const AVLTree<T>& tree);
      
      // assignment operator
      AVLTree<T>& operator= (const AVLTree<T>& tree);
      
      // standard list handling methods
      virtual void Insert(const T& item);
      virtual void Delete(const T& item); 
};

// allocate an AVLTreeNode; terminate the program on a memory
// allocation error
template <class T>
AVLTreeNode<T> *AVLTree<T>::GetAVLTreeNode(const T& item,
               AVLTreeNode<T> *lptr, AVLTreeNode<T> *rptr)
{
   AVLTreeNode<T> *p;

   p = new AVLTreeNode<T> (item, lptr, rptr);
   if (p == NULL)
   {
      cerr << "Memory allocation failure!\n";
      exit(1);
   }
   return p;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::CopyTree(AVLTreeNode<T> *t)
{
   AVLTreeNode<T> *newlptr, *newrptr, *newNode;
   
   if (t == NULL)
   return NULL;
   
   if (t->Left() != NULL) 
   newlptr = CopyTree(t->Left());
   else
   newlptr = NULL;
 
   if (t->Right() != 0) 
   newrptr = CopyTree(t->Right());
   else
   newrptr = NULL;
 
   newNode = GetAVLTreeNode(t->data, newlptr, newrptr);
   return newNode;
}


template <class T>
void AVLTree<T>::SingleRotateLeft (AVLTreeNode<T>* &p)
{
   AVLTreeNode<T> *rc;

   rc = p->Right();
   p->balanceFactor = balanced;
   rc->balanceFactor = balanced;
   p->Right() = rc->Left();
   rc->Left() = p;
   p = rc;
} 

// rotate clockwise about node p; make lc the new pivot
template <class T>
void AVLTree<T>::SingleRotateRight (AVLTreeNode<T>* & p)
{
   // the left subtree of p is heavy
   AVLTreeNode<T> *lc;

   // assign the left subtree to lc
   lc = p->Left();
   
   // update the balance factor for parent and left child
   p->balanceFactor = balanced;
   lc->balanceFactor = balanced;

   // any right subtree of lc must continue as right subtree
   // of lc. do this by making it a left subtree of p
   p->Left() = lc->Right();

   // rotate p (larger node) into right subtree of lc
   // make lc the pivot node
   lc->Right() = p;
   p = lc;
} 

template <class T>
void AVLTree<T>::DoubleRotateLeft (AVLTreeNode<T>* &p)
{
   AVLTreeNode<T> *rc, *np;
   
   rc = p->Right();
   np = rc->Left();
   if (np->balanceFactor == leftheavy)
   {
      p->balanceFactor = balanced;
      rc->balanceFactor = rightheavy;
   }
   else if (np->balanceFactor == balanced)
   {
      p->balanceFactor = balanced;
      rc->balanceFactor = balanced;
   }
   else
   {
      p->balanceFactor = leftheavy;
      rc->balanceFactor = balanced;
   }
   np->balanceFactor = balanced;
   rc->Left() = np->Right();
   np->Right() = rc;
   p->Right() = np->Left();
   np->Left() = p;
   p = np;
} 

// double rotation right about node p
template <class T>
void AVLTree<T>::DoubleRotateRight (AVLTreeNode<T>* &p)
{
   // two subtrees that are rotated
   AVLTreeNode<T> *lc, *np;

   // in the tree,  node(lc) < nodes(np) < node(p)
   lc = p->Left();		// lc is left child of parent
   np = lc->Right();		// np is right child of lc

	// update balance factors for p, lc, and np
	if (np->balanceFactor == rightheavy)
	{
		p->balanceFactor = balanced;
		lc->balanceFactor = leftheavy;
	}
   else if (np->balanceFactor == balanced)
   {
      p->balanceFactor = balanced;
      lc->balanceFactor = balanced;
   }
   else
   {
      p->balanceFactor = rightheavy;
      lc->balanceFactor = balanced;
   }
   np->balanceFactor = balanced;

   // before np replaces the parent p, take care of subtrees
   // detach old children and attach new children
   lc->Right() = np->Left();
   np->Left() = lc;
   p->Left() = np->Right();
   np->Right() = p;
   p = np;
} 


template <class T>
void AVLTree<T>::UpdateLeftTree (AVLTreeNode<T>* &p,
                         int &reviseBalanceFactor)
{
   AVLTreeNode<T> *lc;
   
   lc = p->Left();             // left subtree is also heavy
   if (lc->balanceFactor == leftheavy) 
   {
      SingleRotateRight(p);    // need a single rotation
      reviseBalanceFactor = 0;
   }
   // is right subtree heavy?
   else if (lc->balanceFactor == rightheavy)
   {
      // make a double rotation
      DoubleRotateRight(p);
      // root is now balanced
      reviseBalanceFactor = 0;
   }
}

template <class T>
void AVLTree<T>::UpdateRightTree (AVLTreeNode<T>* &p,
                           int &reviseBalanceFactor)
{
   AVLTreeNode<T> *rc;
   
   rc = p->Right();
   if (rc->balanceFactor == rightheavy) 
   {
   	SingleRotateLeft(p);
   	reviseBalanceFactor = 0;
   }
   else if (rc->balanceFactor == leftheavy) 
   {
   	DoubleRotateLeft(p);
   	reviseBalanceFactor = 0;
   }
}

// insert a new node using the basic List operation and format
template <class T>
void AVLTree<T>::Insert(const T& item)
{

   // declare AVL tree node pointer. using base class method
   // GetRoot, cast to larger node and assign root pointer
   AVLTreeNode<T> *treeRoot = (AVLTreeNode<T> *)GetRoot(),
               *newNode;
   
   // flag used by AVLInsert to rebalance nodes
   int reviseBalanceFactor = 0;
   
   // get a new AVL tree node with empty poiner fields
   newNode = GetAVLTreeNode(item,NULL,NULL);
   
   // call recursive routine to actually insert the element
   AVLInsert(treeRoot, newNode, reviseBalanceFactor);
   
   // assign new values to data members root, size
   // current in the base class
   root = treeRoot;
   current = newNode;
   size++;
}

template <class T>
void AVLTree<T>:: AVLInsert(AVLTreeNode<T>* & tree,
                AVLTreeNode<T>* newNode, int& reviseBalanceFactor)
{
   // flag indicates change node's balanceFactor will occur
   int rebalanceCurrNode;

   // scan reaches an empty tree; time to insert the new node
   if (tree == NULL)
   {
      // update the parent to point at newNode     
      tree = newNode;

      // assign balanceFactor = 0 to new node
      tree->balanceFactor = balanced;

      // broadcast message; balanceFactor value is modified
      reviseBalanceFactor = 1;       
   }

   // recursively move left if new data < current data
   else if (newNode->data < tree->data)
   {
      AVLInsert(tree->Left(),newNode,rebalanceCurrNode);
      // check if balanceFactor must be updated. 
      if (rebalanceCurrNode)
      {
         // case 3: went left from node that is already heavy
         // on the left. violates AVL condition; rotatate
         if (tree->balanceFactor == leftheavy)
            UpdateLeftTree(tree,reviseBalanceFactor);
            
         // case 1: moving left from balanced node. resulting
         // node will be heavy on left
         else if (tree->balanceFactor == balanced)
         {
            tree->balanceFactor = leftheavy;
            reviseBalanceFactor = 1;
         }
         // case 2: scanning left from node heavy on the
         // right. node will be balanced
         else
         {
            tree->balanceFactor = balanced;
            reviseBalanceFactor = 0;
         }
      }
      else
         // no balancing occurs; do not ask previous nodes
         reviseBalanceFactor = 0;
   }

   // otherwise recursively move right
   else
   {
      AVLInsert(tree->Right(), newNode, rebalanceCurrNode);
      // check if balanceFactor must be updated. 
      if (rebalanceCurrNode)
      {
         // case 2: node becomes balanced
         if (tree->balanceFactor == leftheavy)
         {
            // scanning right subtree. node heavy on left.
            // the node will become balanced
            tree->balanceFactor = balanced;     
            reviseBalanceFactor = 0;
         }
         // case 1: node is initially balanced
         else if (tree->balanceFactor == balanced)
         {
            // node is balanced; will become heavy on right
            tree->balanceFactor = rightheavy;
            reviseBalanceFactor = 1;
         }
         else
            // case 3: need to update node
            // scanning right from a node already heavy on 
            // the right. this violates the AVL condition
            // and rotations are needed.
            UpdateRightTree(tree, reviseBalanceFactor);
      }
      else
         reviseBalanceFactor = 0;
   }
}


template <class T>
AVLTree<T>::AVLTree(void): BinSTree<T>()
{}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
   root=(TreeNode<T> *)CopyTree((AVLTreeNode<T> *)tree.root);
   current = root;
   size = tree.size;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator= (const AVLTree<T>& tree)
{
   ClearList();
   root=(TreeNode<T> *)CopyTree((AVLTreeNode<T> *)tree.root);
   current = root;
   size = tree.size;
   return *this;
}

// Delete is empty. suppress warning message that item not used
#pragma warn -par
// Find the node with value item and delete it.
template <class T>
void AVLTree<T>::Delete(const T& item)
{
}

// spacing between levels
const int indentAVLBlock = 6;

// inserts num blanks on the current line
void IndentAVLBlanks(int num)
{
   for(int i = 0;i < num; i++) 
      cout << " ";
}

// print an AVL tree sideways using an RNL tree traversal
template <class T>
void AVLPrintTree (AVLTreeNode<T> *t, int level)
{
   // print tree with root t, as long as t != NULL
   if (t != NULL)
   {
      // print right branch of AVL tree t
      AVLPrintTree(t->Right(),level + 1);
      // indent. output node data and balance factor
      IndentAVLBlanks(indentAVLBlock*level);
      cout << t->data << ':' << t->GetBalanceFactor()<<endl;
      // print left branch of AVL tree t
      AVLPrintTree(t->Left(),level + 1);
   }
}

#endif // AVLTREE_CLASS
