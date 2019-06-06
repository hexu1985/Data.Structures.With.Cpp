#ifndef SEQ_LISTS_WITH_INHERITANCE
#define SEQ_LISTS_WITH_INHERITANCE

#include <iostream.h>
#include <stdlib.h>

#include "iterator.h"
#include "list.h"
#include "link.h"

#ifndef NULL
#define NULL
const int NULL = 0;
#endif

template <class T>
class SeqListIterator;

template <class T>
class SeqList: public List<T>
{
   protected:
      // linked list object, available to a derived class  
      LinkedList<T> llist;
      
   public:
      // constructor
      SeqList(void);

      // list access methods
      virtual int Find (T& item);
      T GetData(int pos);

      // list modification methods        
      virtual void Insert(const T& item);
      virtual void Delete(const T& item);
      T DeleteFront(void);
      virtual void ClearList(void);

      // SeqListIterator needs access to llist
      friend class SeqListIterator<T>;
};

// default constructor. initialize the base class
template <class T>
SeqList<T>::SeqList(void): List<T>()
{}
                        
// use method ClearList to clear the linked list
template <class T>
void SeqList<T>::ClearList(void)
{
   llist.ClearList();
   size = 0;
}

// use method InsertRear to add item at the rear of the list
template <class T>
void SeqList<T>::Insert(const T& item)
{
   llist.InsertRear(item);
   size++;	// update size in List
}

// use method DeleteFront to remove first item from the list
template <class T>
T SeqList<T>::DeleteFront(void)
{
   size--;
   return llist.DeleteFront();
}
   
// delete node whose data value matches item
template <class T>
void SeqList<T>::Delete(const T& item)
{
   int result = 0;
   
   // search for item in list. if found, set result to True
   for(llist.Reset();!llist.EndOfList();llist.Next())
      if (item == llist.Data())
      {
         result++;
         break;
      }
   
   // if item is found, delete it and decrement size
   if (result)
   {
      llist.DeleteAt();
      size--;
   } 
}

// return the data value of item at position pos
template <class T>
T SeqList<T>::GetData(int pos)
{
   // check for a valid position
   if (pos < 0 || pos >= llist.ListSize())
   {
      cerr << "pos is out of range!" << endl;
      exit(1);
   }
   
   // set current linked list position to pos and return data
   llist.Reset(pos);
   return llist.Data();
}

// Take item as key and search the list. return True if item
// is in the list and False otherwise. If found,
// assign the list element to the reference parameter item
template <class T>
int SeqList<T>::Find (T& item)
{
   int result = 0;
   
   // search for item in list. if found, set result to True
   for(llist.Reset();!llist.EndOfList();llist.Next())
      if (item == llist.Data())
      {
         result++;
         break;
      }
   
   // if True, update item and return True; else, return False
   if (result)
      item = llist.Data();
   return result;
}

// SeqListIterator derived from the abstract class Iterator
template <class T>
class SeqListIterator: public Iterator<T>
{
   private:
      // maintain a local pointer to SeqList we are traversing
      SeqList<T> *listPtr;
      // must maintain previous and current positions as we
      // traverse the list
      Node<T> *prevPtr, *currPtr;

   public:
      // constructor
      SeqListIterator(SeqList<T>& lst);
      
      // Traversal methods we must define
      virtual void Next(void);
      virtual void Reset(void);
      
      // Data retrieval/modification method we must define
      virtual T& Data(void);
      
      // reset iterator to traverse a new list
      void SetList(SeqList<T>& lst);
};

// constructor. initialize base class and SeqList pointer
template <class T>
SeqListIterator<T>::SeqListIterator(SeqList<T>& lst):
      Iterator<T>(), listPtr(&lst)
{
   // account for the fact that the list could be empty
   iterationComplete = listPtr->llist.ListEmpty();
   // position the iterator at the front of the list
   Reset();
}

// advance to the next list element
template <class T>
void SeqListIterator<T>::Next(void)
{
   // if currPtr is NULL, we are at end of list
   if (currPtr == NULL)
      return;
   
   // move prevPtr/currPtr forward one node
   prevPtr = currPtr;
   currPtr = currPtr->NextNode();
   
   // if we have arrived at end of linked list, signal that
   // iteration is complete
   if (currPtr == NULL)
      iterationComplete = 1;
}

// move to the beginning of the list
template <class T>
void SeqListIterator<T>::Reset(void)
{
   // reasssign the state of the iteration
   iterationComplete = listPtr->llist.ListEmpty();
   
   // if the list is empty, return
   if (listPtr->llist.front == NULL)
      return;
      
   // move list traversal mechanism to the first node
   prevPtr = NULL;
   currPtr = listPtr->llist.front;
}

// return the data value in the current list element
template <class T>
T& SeqListIterator<T>::Data(void)
{
   // error if list is empty or the traversal has completed
   if (listPtr->llist.ListEmpty() || currPtr == NULL)
   {
      cerr << "Data: invalid reference!" << endl;
      exit(1);
   }
   return currPtr->data;
}

// iterator now traverses lst. reassign listPtr and call Reset
template <class T>
void SeqListIterator<T>::SetList(SeqList<T>& lst)
{
   listPtr = &lst;
   
   // position traversal at 1st data value in new list
   Reset();
}

#endif   // SEQ_LISTS_WITH_INHERITANCE
