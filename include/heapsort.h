#ifndef HEAP_SORT
#define HEAP_SORT

// include the Heap class
#include "heap.h"

// sort array A in descending order
template <class T>
void HeapSort (T A[], int n)
{
   // array A is bound to Heap H
   Heap<T> H(A,n);
   T elt;
   
   // iteration that loads element A[n-1] ... A[1]
   for(int i = n-1;i >= 1;i--)
   {
      // delete smallest element from heap and store in A[i]
      elt = H.Delete();
      A[i] = elt;
   }
}

#endif   // HEAP_SORT
