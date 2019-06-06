#ifndef DATATYPE_SEARCH_METHODS
#define DATATYPE_SEARCH_METHODS

// search the n element arrray a for a match with key
// using the sequential search. return the index of the
// matching array element or -1 if a match does not occur
int SeqSearch(DataType list[], int n, DataType key)
{
   for(int i=0;i < n;i++)
      if (list[i] == key)
         return i;            // return index of the matching item
   return -1;                 // search failed. return -1
}

// search a sorted arrray a for a match with key
// using the binary search. return the index of the
// matching array element or -1 if a match does not occur
int BinSearch(DataType list[], int low, int high, DataType key)
{
   int mid;
   DataType midvalue;

   while (low <= high)
   {
      mid = (low+high)/2;     // mid index in the sublist
      midvalue = list[mid];   // value at the mid index
      if (key == midvalue)    
         return mid;          // have a match. return its location
      else if (key < midvalue)
         high = mid-1;        // go to lower sublist
      else
         low = mid+1;         // go to upper sublist
   }
   return -1;                 // did not find the item
}

#endif   // DATATYPE_SEARCH_METHODS