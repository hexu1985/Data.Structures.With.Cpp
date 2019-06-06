#ifndef BINARY_SEARCH_TREE_CLASS
#define BINARY_SEARCH_TREE_CLASS

#include <iostream.h>
#include <stdlib.h>

#ifndef NULL
const int NULL = 0;
#endif  // NULL

#include "treenode.h"

template <class T>
class BinSTree
{
    protected: // needed for use with inheritance in Chapter 12
        // pointer to tree root and node most recently accessed
        TreeNode<T> *root;
        TreeNode<T> *current;
        
        // number of elements in the tree
        int size;
    
        // memory allocation/deallocation
        TreeNode<T> *GetTreeNode(const T& item,
                        TreeNode<T> *lptr,TreeNode<T> *rptr);
        void FreeTreeNode(TreeNode<T> *p);
        
        // used by copy constructor and assignment operator
        TreeNode<T> *CopyTree(TreeNode<T> *t);
        
        // used by destructor, assignment operator and ClearList
        void DeleteTree(TreeNode<T> *t);

        // locate a node with data item and its parent in tree.
        // used by Find and Delete
        TreeNode<T> *FindNode(const T& item,
                              TreeNode<T>* & parent) const;

    public:
        // constructors, destructor
        BinSTree(void);
        BinSTree(const BinSTree<T>& tree);
        ~BinSTree(void);
        
        // assignment operator
        BinSTree<T>& operator= (const BinSTree<T>& rhs);
        
        // standard list handling methods
        int Find(T& item);
        void Insert(const T& item);
        void Delete(const T& item);
        void ClearList(void);
        int ListEmpty(void) const;
        int ListSize(void) const;
        
        // tree specific methods
        void Update(const T& item);
        TreeNode<T> *GetRoot(void) const;
};

// allocate a new tree node and return a pointer to it
template <class T>
TreeNode<T> *BinSTree<T>::GetTreeNode(const T& item,TreeNode<T> *lptr,TreeNode<T> *rptr)
{
    TreeNode<T> *p;

    // the data field and both pointers are initialized
    p = new TreeNode<T> (item, lptr, rptr);
    if (p == NULL)
    {
        cerr << "Memory allocation failure!\n";
        exit(1);
    }
    return p;
}

// delete the storage occupied by a tree node
template <class T>
void BinSTree<T>::FreeTreeNode(TreeNode<T> *p)
{
    delete p;
}

// copy tree t and make it the tree stored in the current object
template <class T>
TreeNode<T> *BinSTree<T>::CopyTree(TreeNode<T> *t)
{
    TreeNode<T> *newlptr, *newrptr, *newNode;
   
    // if tree branch NULL, return NULL
    if (t == NULL)
        return NULL;
        
    // copy the left branch of root t and assign its root to newlptr
    if (t->left != NULL) 
        newlptr = CopyTree(t->left);
    else
        newlptr = NULL;
 
    // copy the right branch of tree t and assign its root to newrptr
    if (t->right != NULL) 
        newrptr = CopyTree(t->right);
    else
        newrptr = NULL;
 
    // allocate storage for the current root node and assign its data value
    // and pointers to its subtrees. return its pointer
    newNode = GetTreeNode(t->data, newlptr, newrptr);
    return newNode;
}

// delete the tree stored by the current object
template <class T>
void BinSTree<T>::DeleteTree(TreeNode<T> *t)
{
    // if current root node is not NULL, delete its left subtree,
    // its right subtree and then the node itself
    if (t != NULL)
    {
        DeleteTree(t->left);
        DeleteTree(t->right);
        FreeTreeNode(t);
    }
}

// search for data item in the tree. if found, return its node
// address and a pointer to its parent; otherwise, return NULL
template <class T>
TreeNode<T> *BinSTree<T>::FindNode(const T& item,
                                   TreeNode<T>* & parent) const
{   
    // cycle t through the tree starting with root
    TreeNode<T> *t = root;
    
    // the parent of the root is NULL
    parent = NULL;
    
    // terminate on on empty subtree
    while(t != NULL)
    {
        // stop on a match
        if (item == t->data)
            break;
        else 
        {
            // update the parent pointer and move right or left
            parent = t;
            if (item < t->data)
                t = t->left;
            else 
                t = t->right;
        }
    }
    
    // return pointer to node; NULL if not found
    return t;
}

// constructor. initialize root,current to NULL, size to 0
template <class T>
BinSTree<T>::BinSTree(void): root(NULL),current(NULL),size(0)
{}

// copy constructor
template <class T>
BinSTree<T>::BinSTree(const BinSTree<T>& tree)
{
    // copy tree to the current object. assign current and size
    root = CopyTree(tree.root);
    current = root;
    size = tree.size;
}

// destructor
template <class T>
BinSTree<T>::~BinSTree(void)
{
    // just call ClearList
    ClearList();
}

// assignment operator
template <class T>
BinSTree<T>& BinSTree<T>::operator= (const BinSTree<T>& rhs)
{
    // can't copy a tree to itself
    if (this == &rhs)
        return *this;
        
    // clear current tree. copy new tree into current object
    ClearList();
    root = CopyTree(rhs.root);
    
    // assign current to root and set the tree size
    current = root;
    size = rhs.size;
    
    // return reference to current object
    return *this;
}

// search for item. if found, assign the node data to item
template <class T>
int BinSTree<T>::Find(T& item)
{
    // we use FindNode, which requires a parent parameter
    TreeNode<T> *parent;

    // search tree for item. assign matching node to current
    current = FindNode (item, parent);
    
    // if item found, assign data to item and return True
    if (current != NULL)
    {
        item = current->data;
        return 1;
    }
    else
    	// item not found in the tree. return False
        return 0;
}

// insert item into the search tree
template <class T>
void BinSTree<T>::Insert(const T& item)
{
    // t is current node in traversal, parent the previous node
    TreeNode<T> *t = root, *parent = NULL, *newNode;

    // terminate on on empty subtree
    while(t != NULL)
    {
        // update the parent pointer. then go left or right
        parent = t;
        if (item < t->data)
            t = t->left;
        else 
            t = t->right;
    }
    
    // create the new leaf node
    newNode = GetTreeNode(item,NULL,NULL);
    
    // if parent is NULL, insert as root node
    if (parent == NULL)
        root = newNode;
        
    // if item < parent->data, insert as left child        
    else if (item < parent->data)                   
        parent->left = newNode;
        
    else
        // if item >= parent->data, insert as right child     
        parent->right = newNode;
        
    // assign current as address of new node and increment size
    current = newNode;
    size++;
}

// if item is in the tree, delete it
template <class T>
void BinSTree<T>::Delete(const T& item)
{
    // DNodePtr = pointer to node D that is deleted
    // PNodePtr = pointer to parent P of node D
    // RNodePtr = pointer to node R that replaces D
    TreeNode<T> *DNodePtr, *PNodePtr, *RNodePtr;
    
    // search for a node containing data value item. obtain its
    // node address and that of its parent
    if ((DNodePtr = FindNode (item, PNodePtr)) == NULL)
        return;
    
    // If D has a NULL pointer, the
    // replacement node is the one on the other branch
    if (DNodePtr->right == NULL)
        RNodePtr = DNodePtr->left;
    else if (DNodePtr->left == NULL)
        RNodePtr = DNodePtr->right;
        
    // Both pointers of DNodePtr are non-NULL.
    else
    {
        // Find and unlink replacement node for D.
        // Starting on the left branch of node D,
        // find node whose data value is the largest of all
        // nodes whose values are less than the value in D.
        //  Unlink the node from the tree.
        
        // PofRNodePtr = pointer to parent of replacement node
        TreeNode<T> *PofRNodePtr = DNodePtr;
        
        // first possible replacement is left child of D
        RNodePtr = DNodePtr->left;
    
        // descend down right subtree of the left child of D,
        // keeping a record of current node and its parent.
        // when we stop, we have found the replacement
        while(RNodePtr->right != NULL)
        {
            PofRNodePtr = RNodePtr;
            RNodePtr = RNodePtr->right;
        }
        
        if (PofRNodePtr == DNodePtr)
            // left child of deleted node is the replacement.
            // assign right subtree of D to R
            RNodePtr->right = DNodePtr->right;
        else
        {
            // we moved at least one node down a right branch
            // delete replacement node from tree by assigning
            // its left branch to its parent
            PofRNodePtr->right = RNodePtr->left;
            
            // put replacement node in place of DNodePtr.
            RNodePtr->left = DNodePtr->left;
            RNodePtr->right = DNodePtr->right;
        }
    }

    // complete the link to the parent node.
    
    // deleting the root node. assign new root
    if (PNodePtr == NULL)
        root = RNodePtr;
        
    // attach R to the correct branch of P
    else if (DNodePtr->data < PNodePtr->data)
        PNodePtr->left = RNodePtr;
    else
        PNodePtr->right = RNodePtr;
        
    // delete the node from memory and decrement list size
    FreeTreeNode(DNodePtr);
    size--;
}

// delete all the nodes in the tree. current now NULL and size is 0
template <class T>
void BinSTree<T>::ClearList(void)
{
    DeleteTree(root);
    root = NULL;
    current = NULL;
    size = 0;
}

// indicate whether the tree is empty
template <class T>
int BinSTree<T>::ListEmpty(void) const
{
    return root == NULL;
}

// return the number of data items in the tree
template <class T>
int BinSTree<T>::ListSize(void) const
{
    return size;
}

// if current node is defined and its data value matches item,
// assign node value to item ; otherwise, insert item in tree
template <class T>
void BinSTree<T>::Update(const T& item)
{   
    if (current != NULL && current->data == item)
            current->data = item;
    else
        Insert(item);
}

// return the address of the root node.
template <class T>
TreeNode<T> *BinSTree<T>::GetRoot(void) const
{
    return root;
}

#endif  // BINARY_SEARCH_TREE_CLASS
