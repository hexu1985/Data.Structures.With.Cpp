#ifndef ARRAY_ITERATOR
#define ARRAY_ITERATOR

#include <iostream.h>
#include <stdlib.h>

#include "iterator.h"
#include "array.h"

template <class T>
class ArrayIterator: public Iterator<T>
{
   private:
      // current location, starting and ending points
      int currentIndex;
      int startIndex;
      int finishIndex;
      
      // address of the Array object that we must traverse
      Array<T> *arr;
   public:
      // constructor
      ArrayIterator(Array<T>& A,int start=0,int finish=-1);
      
      // standard iterator operations required by base class
      virtual void Next(void);
      virtual void Reset(void);
      virtual T& Data(void);
};

// constructor. initialize the base class and data members
template <class T>
ArrayIterator<T>::ArrayIterator(Array<T>& A,int start,
                                int finish): arr(&A)
{
   // last available array index
   int ilast = A.ListSize() - 1;
   
   // initialize index values. if finish == -1,
   // traverse whole array
   currentIndex = startIndex = start;
   finishIndex = finish != -1 ? finish : ilast;
   
   // indices must be in range of array
   if (!((startIndex>=0 && startIndex<=ilast) &&
        (finishIndex>=0 && finishIndex<=ilast) &&
        (startIndex <= finishIndex)))
   {
      cerr << "ArrayIterator: Index parameter incorrect!"
           << endl;
      exit(1);
   }
}

// reset to the start of the array
template <class T>
void ArrayIterator<T>::Reset(void)
{
   // set current index to starting traversal index
   currentIndex = startIndex;
   
   // the iteration is not complete yet
   iterationComplete = 0;
}

// return the value of the current array element
template <class T>
T& ArrayIterator<T>::Data(void)
{
   // can't call Data if have traversed entire array
   if(iterationComplete)
   {
      cerr << "Iterator has passed the end of the list!"
           << endl;
      exit(1);
   }
   
   return (*arr)[currentIndex];
}

// advance to the next array element
template <class T>
void ArrayIterator<T>::Next(void)
{
   // if iteration is not complete, increment currentIndex.
   // if it passes finishIndex, the iteration is complete
   if (!iterationComplete)
   {
       currentIndex++;
       if(currentIndex > finishIndex)
          iterationComplete = 1;
   }
}

#endif   // ARRAY_ITERATOR
