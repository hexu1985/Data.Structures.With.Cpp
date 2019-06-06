#ifndef TEMPLATE_UTILITY_FUNCTIONS
#define TEMPLATE_UTILITY_FUNCTIONS

#include <string.h>

// using key, search the n element arrray list for a match.
// if found, return a pointer to the data; otherwise return NULL 
template <class T>
int SeqSearch(T list[], int n, T key)
{
    for(int i=0;i < n;i++)
       if (list[i] == key)
            return i;    // return index to matching item
    return -1;            // search failed. return -1
}

#include "array.h"

// recursive version of the binary search to locate
// a key in an ordered array A
template <class T>
int BinSearch(T A[], int low, int high, T key)
{
    int mid;
    T midvalue;

    // key not found is a stopping condition
    if (low > high)
        return(-1);

    // compare against list midpoint and subdivide
    // if a match does not occur. apply binary
    // search to the appropriate sublist
    else
    {
        mid = (low+high)/2;
        midvalue = A[mid];
        // stopping condition if key matched
        if (key == midvalue)
            return(mid);    // key found at index mid

        // look left if key < midvalue; otherwise, look right
        else if (key < midvalue)
            // recursive step
            return BinSearch(A,low,mid-1,key);
        else
            // recursive step
            return BinSearch(A,mid+1,high,key);
    }
}

#endif  // TEMPLATE_UTILITY_FUNCTIONS
