#ifndef LONG_RUNS
#define LONG_RUNS

// include the class PQueue for PQ1 and PQ2
#include "pqueue.h"

template <class T>
class LongRunFilter
{
   private:
      // pointers that identify the key parameters in the filter
      // A is the list, PQ1 and PQ2 are the two priority queues
      T  *A;
      PQueue<T>   *PQ1, *PQ2;
      int  loadIndex;
      
      // gives the size of the array and the priority queue 
      int arraySize;
      int filterSize;
      
      // copy entries from priority queue PQ2 to PQ1 
      void CopyPQ (void);
      
      // loads items from the array A into the priority queue
      void LoadPQ (void);

   public:
      // constructor and destructor
      LongRunFilter(T arr[],int n, int sz); 
      ~LongRunFilter(void); 
      
      // create long runs
      void LoadRuns(void);
      
      // evaluating the runs
      void PrintRuns(void) const;
      int  CountRuns(void) const;
};

// constructor to convert an array to a priority queue.
// the array and its size are passed as parameters
template <class T>
LongRunFilter<T>::LongRunFilter(T arr[],int n, int sz) :
				  arraySize(n), A(arr), filterSize(sz)
{
   if (filterSize != 0)
   {
   		loadIndex = 0;
   		PQ1 = new PQueue<T>(filterSize);
   		PQ2 = new PQueue<T>(filterSize);
   		// move first batch of elements from array to PQ1
   		LoadPQ();
   }
}

// destructor deallocates memory for priority queues
template <class T>
LongRunFilter<T>::~LongRunFilter(void)
{
   if (filterSize != 0)
   {
   		delete [] PQ1, PQ2;
   }
}

// copy elements from PQ2 that holds elements for the
// next run into PQ1, the priory queue for the current run
template <class T>
void LongRunFilter<T>::CopyPQ (void)
{
   T  temp;
   while (!PQ2->PQEmpty())
   {
      temp = PQ2->PQDelete();
      PQ1->PQInsert(temp);
   }
}

// load elements from the array A into priority queue PQ1
template <class T>
void LongRunFilter<T>::LoadPQ (void)
{
   int   k;
 
 	// first copy elements from PQ2 into PQ1  
   CopyPQ();
   
   // determine how many elements are in PQ1
   k = PQ1->PQLength();
   // fill out PQ1 until the queue is full or te  array
   // A is exhausted
   while (loadIndex < arraySize && k < filterSize)
   {
      PQ1->PQInsert(A[loadIndex++]);
      k++;
   }
}

// scan array A and create long runs by running the elements
// througth the filter
template <class T>
void LongRunFilter<T>::LoadRuns(void)
{
   T  value;
   int currIndex = 0;
   
   if (filterSize == 0)
   		return;
   
   // start by loading the smallest element from PQ1 into A
   A[currIndex] = PQ1->PQDelete();
   
   // PQ1 has the first filterSize elements of A
   // now look at the remaining elements in A 
   while (loadIndex < arraySize)
   {
   	  // look at next element from the list
   	  value = A[loadIndex++];
   	  // if element is larger than entry in current run,
   	  // it belongs to the current run and is put in PQ1;
   	  // otherwise put it in PQ2 that holds items for next run
      if (A[currIndex] <= value)
         PQ1->PQInsert(value);
      else
         PQ2->PQInsert(value);
      // once PQ1 is empty, current run is complete. copy the
      // elements from PQ2 to PQ1 and begin the next run  
      if (PQ1->PQEmpty())
      	 CopyPQ();
  
      // extract element from PQ1 and put in the run
      if (!PQ1->PQEmpty())
      	 A[++currIndex] = PQ1->PQDelete();
   }
    
    // clean up elements from current run and then from
    // the next run.      
	while (!PQ1->PQEmpty())
		A[++currIndex] = PQ1->PQDelete();
	while (!PQ2->PQEmpty())
		A[++currIndex] = PQ2->PQDelete();
}

// scan the list and print each element.  move to next
// line from the begiing of the next run
template <class T>
void LongRunFilter<T>::PrintRuns(void) const
{
   int i = 1;
   cout << A[0] <<"  ";

   do
   {
      if (A[i] < A[i-1])
         cout << endl;
      cout << A[i++] <<"   ";
   }
   while (i < arraySize);
   cout << endl;
}

// scan the list and count the number of runs.
template <class T>
int LongRunFilter<T>::CountRuns(void) const
{
   int i = 1, count = 1;
   
   if (arraySize == 0)
   	  return 0;
   else
   	while (i < arraySize)
   	{
   		if (A[i] < A[i-1])
   			count++;
   		i++;
   	}
   return count;
}
#endif // LONG_RUNS
