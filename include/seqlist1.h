#ifndef SEQLIST_CLASS
#define SEQLIST_CLASS

#include <iostream.h>
#include <stdlib.h>

#include "link.h"

template <class T>
class SeqList
{
	private:
		// linked list object	 
		LinkedList<T> llist;
        
	public:
		// constructor
		SeqList(void);

		// list access methods
		int ListSize(void) const;                    
		int ListEmpty(void) const;
		int Find (T& item);
		T GetData(int pos);

		// list modification methods        
		void Insert(const T& item);
		void Delete(const T& item);
		T DeleteFront(void);
		void ClearList(void);
};

// default constructor. it has nothing to do.
template <class T>
SeqList<T>::SeqList(void)
{}
                                
// use method ListSize to return number elements in list 
template <class T>
int SeqList<T>::ListSize(void) const
{
    return llist.ListSize();
}
                                
// use method ListEmpty to test for an empty list
template <class T>
int SeqList<T>::ListEmpty(void) const
{
    return llist.ListEmpty();
}

// use method ClearList to clear the linked list
template <class T>
void SeqList<T>::ClearList(void)
{
    llist.ClearList(); 
}

// use method InsertRear to add item at the rear of the list
template <class T>
void SeqList<T>::Insert(const T& item)
{
	llist.InsertRear(item);
}

// use method DeleteFront to remove first item from the list
template <class T>
T SeqList<T>::DeleteFront(void)
{
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
	
	// if item is found, delete it; otherwise return
	if (result)
		llist.DeleteAt(); 
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

// take item as the key and search the list. return True if item
// is in the list and False otherwise. if found,
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
	
	// if result is True, update item and return True; 
	// otherwise, return False
	if (result)
	    item = llist.Data();
	return result;
}

#endif  // SEQLIST_CLASS
