#ifndef __UTILS__
#define __UTILS__

#include <string.h>

// using key, search the n element arrray list for a match.
// if found return index at the match; otherwise return -1 
template <class T>
int SeqSearch(T list[], int n, T key)
{
    for(int i=0;i < n;i++)
       if (list[i] == key)
            return i;   // return index of matching item
   return -1;           // search failed. return -1
} 

// search array of strings for match with string key
int SeqSearch(char *list[], int n, char *key)
{
    for(int i=0;i < n;i++)
        // compare using C++ string library function
        if (strcmp(list[i],key) == 0)
            return i;   // return index at match          
    return -1;          // return -1 on failure
}

// sort the n element a using the exchange sort algorithm
template <class T>
void ExchangeSort(T a[], int n)
{
    T temp;
    int i, j;
    
    // make n-1 passes
    for (i = 0; i < n-1; i++)
        // put smallest of a[i+1]...a[n-1] in a[i]
        for (j = i+1; j < n; j++)
            if (a[j] < a[i])
            {
                // swap a[i] and a[j]
                temp = a[i];
                a[i] = a[j];          
                a[j] = temp;
            }
}

#endif  // __UTILS__