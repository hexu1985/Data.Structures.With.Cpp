#include <iostream.h>

// search the n element integer arrray a for a match with key
// return a pointer to the data or NULL if the key is not found.
int SeqSearch(int list[], int start, int n, int key)
{
    for(int i=start;i < n;i++)
	if (list[i] == key)
	    return i;           // return index of matching item
    return -1;                          // search failed. return -1
}

void main(void)
{
    int A[10];
    int key, count = 0, pos;

    // prompt for and enter a list of 10 integers
    cout << "Enter a list of 10 integers: ";
    for (pos=0; pos < 10; pos++)
	cin >> A[pos];

    cout << "Enter a key: ";
    cin >> key;
    
    // start search at first array element
    pos = 0;
    
    // move through list as long as key is found
    while ((pos = SeqSearch(A,pos,10,key)) != -1)
    {
	count++;
	// move to next integer after match
	pos++;
    }
    
    cout << key << " occurs " << count
	 << (count != 1 ? " times" : " time")
	 << " in the list." << endl;
}

/*
<Run of Program 2.3>

Enter a list of 10 integers: 5 2 9 8 1 5 8 7 5 3
Enter a key: 5
5 occurs 3 times in the list.
*/


