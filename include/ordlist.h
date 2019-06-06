#ifndef ORDERED_LIST_CLASSS
#define ORDERED_LIST_CLASSS

#include "seqlist2.h"

template <class T>
class OrderedList: public SeqList<T>
{
   public:
      // constructor
      OrderedList(void);
      
      // override Insert to form an ordered list.
      virtual void Insert(const T& item);
};

// constructor. initialize the base class
template <class T>
OrderedList<T>::OrderedList(void): SeqList<T>()
{}

// insert item into the list in ascending order
template <class T>
void OrderedList<T>::Insert(const T& item)
{
   // use the linked list traversal mechanism to locate the
   // insertion point
   for(llist.Reset();!llist.EndOfList();llist.Next())
      if (item < llist.Data())
         break;
         
   // insert item at the current list location
   llist.InsertAt(item);
   size++;
}

#endif   // ORDERED_LIST_CLASSS
