#ifndef TREE_SCANS
#define TREE_SCANS

#include "treenode.h"
#include "queue.h"
#include "stack.h"


#ifndef NULL
const int NULL = 0;
#endif    // NULL

// preorder recursive scan of the nodes in a tree
// recursive calls use <T> to compensate for bug in VC++
template <class T>
void Preorder (TreeNode<T> *t, void visit(T& item))
{ 
   // the recursive scan terminates on a empty subtree      
   if (t != NULL)
   {
      visit(t->data);               // visit the node
      Preorder<T> (t->Left(), visit);   // descend left
      Preorder<T> (t->Right(), visit);  // descend right
   }
}

// inorder recursive scan of the nodes in a tree
// recursive calls use <T> to compensate for bug in VC++
template <class T>
void Inorder (TreeNode<T> *t, void visit(T& item))
{
   // the recursive scan terminates on a empty subtree
   if (t != NULL)
   {
      Inorder<T> (t->Left(), visit);	// descend left
      visit(t->data);						// visit the node
      Inorder<T> (t->Right(), visit);  // descend right
   }
}

// postorder recursive scan of the nodes in a tree
// recursive calls use <T> to compensate for bug in VC++
template <class T>
void Postorder (TreeNode<T> *t, void visit(T& item))
{
   // the recursive scan terminates on a empty subtree
   if (t != NULL)
   {
      Postorder<T> (t->Left(), visit);  // descend left
      Postorder<T> (t->Right(), visit); // descend right
      visit(t->data);               // visit the node
   }
}

// traverse the list by level by level and visit each node
template <class T>
void LevelScan(TreeNode<T> *t, void visit(T& item))
{
   // store siblings of each node in a queue so that they are
   // visited in order at the next level of the tree
   Queue<TreeNode<T> *> Q;
   TreeNode<T> *p;

   // initialize the queue by inserting the root in the queue
   Q.QInsert(t);
   
   // continue the iterative process until the queue is empty
   while(!Q.QEmpty())
   {
      // delete front node from queue and execute visit function
      p = Q.QDelete();
      visit(p->data); 
            
      // if a left child exists, insert it in the queue
      if(p->Left() != NULL)
       Q.QInsert(p->Left());
      // if a right child exists, insert next to its sibling
      if(p->Right() != NULL)
       Q.QInsert(p->Right());
   }
}

// return address of last node on the left branch from t,
// stacking nodes on the way. used for iterative inorder scan.
template <class T>
TreeNode<T> *GoFarLeft(TreeNode<T> *t,Stack<TreeNode<T> *>& S)
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

// inorder iterative scan
template <class T>
void Inorder_I(TreeNode<T> *t, void visit(T& c))
{  
   // stack to hold node address on a left branch
   Stack<TreeNode<T> *> S;
   
   // get address of last node on the left branch from t.
   // this is the first node in the scan
   t = GoFarLeft(t,S);
   
   // continue until t is NULL
   while(t != NULL)
   {
      // we have gone left. visit the node
      visit(t->data);
      
      // if have a right subtree, move right and go far left,
      // stacking up nodes on the left subtree
      if (t->Right() != NULL)
       t = GoFarLeft(t->Right(),S);
       
      // there is no right subtree but there are nodes we have
      // stacked that we must process. pop and continue
      else if (!S.StackEmpty())     // move up the tree
       t = S.Pop();
       
      // no more right branches or stacked nodes to process
      else
       t = NULL;   // we are done
   }
}

#endif    // TREE_SCANS
