#ifndef ARRAY_BASED_SORTING_FUNCTIONS
#define ARRAY_BASED_SORTING_FUNCTIONS

// swap values of x and y. used by all the
// sorting algorithms here
template <class T>
void Swap (T &x, T &y)
{
   T temp;
   
   temp = x;
   x = y;
   y = temp;
}

// sort an array of n elements of type T using the
// exchange sort algorithm
template <class T>
void ExchangeSort(T a[], int size)
{
   int i, j;
   
	// make size-1 passes through the data
	for (i = 0; i < size-1; i++)
   	// locate least of a[i]...a[size-1] at a[i]
      for (j = i+1; j < size; j++)
         if (a[j] < a[i])
            Swap(a[j],a[i]);
}

// sort an array of n elements of type T using the
// selection sort algorithm
template <class T>
void SelectionSort(T A[], int n)
{
   // index of smallest item in each pass
   int smallIndex;            
   int i, j;

   // sort A[0]..A[n-2], and A[n-1] is in place
   for (i = 0; i < n-1; i++) 
   {
      // start the scan at index i; set smallIndex to i
      smallIndex = i;
      // j scans the sublist A[i+1]..A[n-1]
      for (j = i+1; j < n; j++) 
         // update smallIndex if smaller element is found 
         if (A[j] < A[smallIndex])
            smallIndex = j;
      // when finished,  place smallest item in A[i]
      Swap(A[i], A[smallIndex]);
   }
}

// BubbleSort is passed an array A and list count n. it
// sorts the data by making a series of passes as long as
// lastExchangeIndex > 0.
template <class T>
void BubbleSort(T A[], int n)
{
   int i,j;             
   // Index of last exchange 
   int lastExchangeIndex;

   // i is the index of last element in the sublist
   i = n-1;

   // continue the process until no exchanges are made
   while (i > 0) 
   {
      // start lastExchangeIndex at 0
      lastExchangeIndex = 0;
      
      // scan the sublist A[0] to A[i]
      for (j = 0; j < i; j++)
         // exchange a pair and update lastExchangeIndex
         if (A[j+1] < A[j])
         { 
            Swap(A[j],A[j+1]);
            lastExchangeIndex = j;
         }

      // set i to index of the last exchange. continue sorting
      // the sublist A[0] to A[i]
      i = lastExchangeIndex;
   }
}

// insertion sort orders sublists A[0] ... A[i], 1 <= i <= n-1.
// for each i, insert A[i] in the correct position A[j]
template <class T>
void InsertionSort(T A[], int n)
{
   int i, j;
   T   temp;

   // i identifies the sublist A[0] to A[i].
   for (i = 1; i < n; i++) 
   {
      // index j scans down list from A[i] looking for 
      // correct position to locate target. assigns it to A[j]
      j = i;
      temp = A[i];
      // locate insertion point by scanning downward as long
      // as temp < A[j-1] and we have not encountered the
      // beginning of the list
      while (j > 0 && temp < A[j-1])
      { 
         // shift elements up list to make room for insertion
         A[j] = A[j-1];
         j--;
      }
      // the location is found; insert the temp
      A[j] = temp;
   }
}

// QuickSort accepts an array and two range parameters
template <class T>
void QuickSort(T A[], int low, int high)
{
   // local variables holding the mid index of the range,
   // its value A[mid] and the scanning indices
   T  pivot;
   int scanUp, scanDown;
   int mid;

   // if the range is not at least two elements, return  
   if (high - low <= 0)
		return;
   else 
   // if sublist has two elements, compare them and
   // exchange their values if necessary
   if (high - low == 1)
   {           
      if (A[high] < A[low]) 
         Swap(A[low], A[high]);
      return;
   }
   
   // get the mid index and assign its value to pivot
   mid = (low + high)/2;
   pivot = A[mid];

   // exchange the pivot and the low end of the range
   // and initialize the indices scanUp and scanDown.
   Swap(A[mid], A[low]);
   scanUp = low + 1;
	scanDown = high;
      
   // manage the indices to locate elements that are in
   // the wrong sublist; stop when scanDown < scanUp 
   do 
   {
		// move up lower sublist; stop when scanUp enters
		// upper sublist or identifies an element > pivot
		while (scanUp <= scanDown && A[scanUp] <= pivot)
         scanUp++;
 
      // scan down upper sublist; stop when scanDown locates 
      // an element <= pivot; we guarantee we stop at A[low]
      while (pivot < A[scanDown])
         scanDown--;
	         
      // if indices are still in their sublists, then they
      // identify two elements in wrong sublists. exchange
      if (scanUp < scanDown)
         Swap(A[scanUp], A[scanDown]);
   } 
   while (scanUp < scanDown);

   // copy pivot to index (scanDown) that partitions sublists 
   A[low] = A[scanDown];
   A[scanDown] = pivot;

   // if the lower sublist (low to scanDown-1) has 2 or more 
   // elements, make the recursive call
   if (low < scanDown-1)
      QuickSort(A, low, scanDown-1);

   // if higher sublist (scanDown+1 to high) has 2 or more 
   // elements, make the recursive call
   if (scanDown+1 < high)
      QuickSort(A, scanDown+1, high);
}

#endif   // ARRAY_BASED_SORTING_FUNCTIONS
