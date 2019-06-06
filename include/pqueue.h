#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream.h>
#include <stdlib.h>

#include "heap.h"

#ifndef NULL
const int NULL = 0;
#endif   // NULL

template <class T>
class PQueue
{
   private:
      // heap that stores the queue list
      Heap<T> *ptrHeap;

   public:
      // constructor
      PQueue   (int sz);
         
      // priority queue modification operations
      void  PQInsert(const T& item);
      T PQDelete(void);
      void ClearPQ(void);
      
      // priority queue test methods
      int PQEmpty(void) const;
      int PQFull(void) const;
      int PQLength(void) const;
};

template <class T> 
PQueue<T>::PQueue(int size)
{
   ptrHeap = new Heap<T> (size);
   if(ptrHeap == NULL)
   {
      cerr << "Memory allocation failure!" << endl;
      exit(1);
   }
}

template <class T> 
void PQueue<T>::PQInsert(const T& item)
{
   ptrHeap->Insert(item);
}

// delete the first element in the quueue by deleting the
// root of the corresponding heap. return the deleted value
template <class T> 
T PQueue<T>::PQDelete(void)
{
   return ptrHeap->Delete();
}

template <class T> 
int PQueue<T>::PQFull(void) const
{
   return ptrHeap->ListFull();
}

template <class T> 
int PQueue<T>::PQEmpty(void) const
{
   return ptrHeap->ListEmpty();
}

template <class T> 
int PQueue<T>::PQLength(void) const
{
   return ptrHeap->ListSize();
}

template <class T> 
void PQueue<T>::ClearPQ(void)
{
   ptrHeap->ClearList();
}

#endif   // PRIORITY_QUEUE
