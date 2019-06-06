#ifndef TREENODE_CLASS
#define TREENODE_CLASS

#ifndef NULL
const int NULL = 0;
#endif  // NULL

// BinStree depends on TreeNode
template <class T>
class BinSTree;

// declares a tree node object for a binary tree
template <class T>
class TreeNode
{
   // protected is needed so the derived class AVLTreeNode
   // of Chapter 13 can access the pointer data. in ordinary
   // TreeNode applications, protected and private are equivalent
   protected:
      // points to the left and right children of the node
      TreeNode<T> *left;
      TreeNode<T> *right;

   public:
      // public member allowing the client to update its value
      T data;
   
      // constructor
      TreeNode (const T& item, TreeNode<T> *lptr = NULL,
                TreeNode<T> *rptr = NULL);
   
      // virtual destructor. needed for AVL tree class
      // developed in Chapter 13
      virtual ~TreeNode(void);
   
      // access methods for the pointer fields
      TreeNode<T>* Left(void) const;
      TreeNode<T>* Right(void) const;
   
      // BinTree needs access to left and right
      friend class BinSTree<T>;
};

// constructor. initialize the data and pointer fields.
// the pointer NULL assigns an empty tree 
template <class T>
TreeNode<T>::TreeNode (const T& item, TreeNode<T> *lptr,
    TreeNode<T> *rptr): data(item), left(lptr), right(rptr)
{}

// method Left allows the user to reference the left child
template <class T>
TreeNode<T>* TreeNode<T>::Left(void) const
{
   // return the private member value left
   return left;
}

// method Left allows the user to reference the right child
template <class T>
TreeNode<T>* TreeNode<T>::Right(void) const
{
   // return the private member value right
   return right;
}

// does nothing. exists so nodes derived from it will be
// destroyed properly by delete. used in Chapter 13 for
// AVL trees
template <class T>
TreeNode<T>::~TreeNode(void)
{}

#endif // TREENODE_CLASS
