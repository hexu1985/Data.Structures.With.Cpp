#ifndef NODE_LIBRARY
#define NODE_LIBRARY

#include <iostream.h>
#include <stdlib.h>
// suppress incorrect warning message in InsertFront
#pragma warn -par

#include "node.h"

// allocate a node with data member item and pointer nextPtr
template <class T>
Node<T> *GetNode(const T& item, Node<T> *nextPtr = NULL)
{
    Node<T>  *newNode;

    // allocate memory while passing item and NextPtr to
    // constructor. terminate program if allocation fails
    newNode = new Node<T>(item, nextPtr);
    if (newNode == NULL)
    {
        cerr << "Memory allocation failure!" << endl;
        exit(1);
    }
    
    return newNode;
}

enum AppendNewline {noNewline,addNewline};

// print a linked list
template <class T>
void PrintList(Node<T> *head, AppendNewline addnl = noNewline)
{
    // currPtr chains through the list, starting at head
    Node<T> *currPtr = head;

	// print the current node's data until end of list
    while(currPtr != NULL)
    {
        // output newline if addl == addNewline
        if(addnl == addNewline)
            cout << currPtr->data << endl;
        else
            cout << currPtr->data << "  ";
           
        // move to next node
        currPtr = currPtr->NextNode();
    }
}

// find an item in a linked list head; return TRUE and
// value of previous pointer if found; otherwise return FALSE
template <class T>
int Find(Node<T> *head, T& item, Node<T>* &prevPtr)
{
	// find node with value item and return 1 if found and
	// 0 otherwise.  also give access to the previous pointer
	// begin traversal at first node
	Node<T> *currPtr = head;

	prevPtr = NULL;
	
	// cycle through the list until end of list
	while(currPtr != NULL)
	{
		// compare data field with item and return if
		// successful; otherwise, go to the next node
		if (currPtr->data == item)
		{
			item = currPtr->data;
			return 1;
		}
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
	
	// failed to locate item
	return 0;
}

// insert item at the front of list
template <class T>
void InsertFront(Node<T>* & head, T item)
{
    // allocate new node so it points to original list head
    // update the list head
    head = GetNode(item,head);
}

// find rear of the list and append item
template <class T>
void InsertRear(Node<T>* & head, const T& item)
{
    Node<T>  *newNode, *currPtr = head;

	// if list is empty, insert item at the front
    if (currPtr == NULL)
        InsertFront(head,item);
    else
    {
		// find the node whose pointer is NULL
    	while(currPtr->NextNode() != NULL)
    		currPtr = currPtr->NextNode();
    		
    	// allocate node and insert at rear (after currPtr)
        newNode = GetNode(item);
        currPtr->InsertAfter(newNode);
    }
}               

// delete the first node of the list
template <class T>
void DeleteFront(Node<T>* & head)
{
	// save the address of node to be deleted
    Node<T> *p = head;

	// make sure list is not empty
    if (head != NULL)
    {
	// move head to second node and delete original
        head = head->NextNode();
        delete p;
    }
}

// delete the first occurrence of key in the list
template <class T>
void Delete (Node<T>* & head, T key)
{
   // currPtr moves through list, trailed by prevPtr
   Node<T>  *currPtr = head, *prevPtr = NULL; 

   // return if the list is empty
   if (currPtr == NULL)
      return;
      
   // cycle list until key is located or come to end
   while (currPtr != NULL && currPtr->data != key)
   {
      // advance currPtr so prevPtr trails it
      prevPtr = currPtr;
      currPtr = currPtr->NextNode();
   }

   // if currPtr != NULL, key located at currPtr.
   if (currPtr != NULL)
   {
      // prevPtr == NULL means match at front node
      if(prevPtr == NULL)
         head = head->NextNode();
      else
         // match occurred at 2nd or subsequent node
         // prevPtr->DeleteAfter() unlinks the node
         prevPtr->DeleteAfter();

      // dispose of the node
      delete currPtr;
   }
}

// insert item into the ordered list
template <class T>
void InsertOrder(Node<T>* & head, T item)
{
    // currPtr moves through list, trailed by prevPtr
    Node<T> *currPtr, *prevPtr, *newNode;
    
    // prevPtr == NULL signals match at front
    prevPtr = NULL;
    currPtr = head;
    
    // cycle through the list and find insertion point
    while (currPtr != NULL)
    {
	// found insertion point if item < current data
	if (item < currPtr->data)
		break;
			
	// advance currPtr so prevPtr trails it
        prevPtr = currPtr;
        currPtr = currPtr->NextNode();
    }   

    // make the insertion
    if (prevPtr == NULL)
	// if prevPtr == NULL, insert at front
        InsertFront(head,item);
    else
    {
	// insert new node after previous
        newNode = GetNode(item);
        prevPtr->InsertAfter(newNode);
    }
}

// delete all the nodes in the linked list
template <class T>
void ClearList(Node<T> * &head)
{
    Node<T> *currPtr, *nextPtr;

	// chain through the list deleting nodes
    currPtr = head;
    while(currPtr != NULL)
    {
	// record address of next node, delete current node
        nextPtr = currPtr->NextNode();
        delete currPtr;
        
        // move current node forward
        currPtr = nextPtr;
    }

    // mark list as empty
    head = NULL;
}

#endif  // NODE_LIBRARY
