#include <iostream.h>

// interchange the values of the two integer variables x and y
void Swap(int & x, int & y)
{
    int temp = x;   // store original value of x

    x = y;          // replace x by y
    y = temp;       // assign y the original value of x
}

// sort the n element integer array a in ascending order.
void ExchangeSort(int a[], int n)
{
    int i, j;

    // implement n-1 passes. locate correct values
    // in a[0],...,a[n-2].  
    for(i = 0; i < n-1; i++)
	// put minumum of a[i+1]...a[n-1] in a[i]
	for(j = i+1; j < n; j++)
	    // exchange if a[i] > a[j]
	    if (a[i] > a[j])
		Swap(a[i], a[j]);
}

// step through the list and print each value.
void PrintList(int a[], int n)
{
    for (int i = 0; i < n; i++)
	cout << a[i] << "  ";
    cout << endl;
}

void main(void)
{
    int list[15] = {38,58,13,15,51,27,10,19,
				12,86,49,67,84,60,25};
    int i;
    
    cout << "Original List\n";
    PrintList(list,15);
    ExchangeSort(list,15);
    cout << endl << "Sorted List" << endl;
    PrintList(list,15);
}

/*
<Run of Program 2.4>

Original List
38  58  13  15  51  27  10  19  12  86  49  67  84  60  25

Sorted List
10  12  13  15  19  25  27  38  49  51  58  60  67  84  86
*/
