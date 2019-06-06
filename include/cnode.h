#ifndef CIRCULAR_NODE_CLASS
#define CIRCULAR_NODE_CLASS

template <class T>
class CNode
{
    private:
    	// circular link to the next node
        CNode<T> *next;
    public:
    	// data is public 
        T data;
        
		// constructors
        CNode(void);
        CNode (const T& item);
        
        // list modification methods
        void InsertAfter(CNode<T> *p);
        CNode<T> *DeleteAfter(void);
        
        // obtain the address of the next node
        CNode<T> *NextNode(void) const;
};

// constructor that creates an empty list and
// leaves the data uninitialized. use for header
template <class T>
CNode<T>::CNode(void)
{
	// initialize the node so it points to itself
    next = this;
}

// constructor that creates an empty list and initializes data
template <class T>
CNode<T>::CNode(const T& item)
{
	// set node to point to itself and initialize data
    next = this;
    data = item;
}
  
// return pointer to the next node
template <class T>
CNode<T> *CNode<T>::NextNode(void) const
{
    return next;
}

// insert a node p after the current one
template <class T>
void CNode<T>::InsertAfter(CNode<T> *p)
{
	// p points to successor of the current node, and current node
	// points to p.
    p->next = next;
    next = p;
}

// delete the node following current and return its address
template <class T>
CNode<T> *CNode<T>::DeleteAfter(void)
{
	// save address of node to be deleted
    CNode<T> *tempPtr = next;
    
	// if next is the address of current object (this), we are
	// pointing to ourself. We don't delete ourself! return NULL
    if (next == this)
        return NULL;
        
	// current node points to successor of tempPtr.
    next = tempPtr->next;
    
	// return the pointer to the unlinked node
    return tempPtr;
}

#endif  // CIRCULAR_NODE_CLASS
