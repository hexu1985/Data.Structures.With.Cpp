// UpperLimit is maximum number of elements to permute
const int UpperLimit = 5;

// copy n element array y to array x
void copy(int x[], int y[], int n)
{
    for (int i=0;i < n;i++)
        x[i] = y[i];
}

// permlist is an n element array of integers. generate
// the permutations of the elements whose indices
// are in the range start <= i <= n-1. when a permutation
// is complete, print the entire array. to permute all n
// elements, begin with start = 0
void permute(int permlist[], int start, int n)
{
    int tmparr[UpperLimit];
    int temp, i;

    // stopping condition: land at last array element
    if (start == n-1)
    {
        // print the permutation
        for (i=0;i < n;i++)
            cout << permlist[i] << "  ";
        cout << endl;
    }
    else
        // recursive step: exchange permlist[start] and
        // permlist[i], make a copy of the array in temparr,
        // and permute elements of tmparr from start+1
        // through end of array
        for (i=start;i < n;i++)
        {
            // exchange permlist[i] with permlist[start]
            temp = permlist[i];
            permlist[i] = permlist[start];
            permlist[start] = temp;
            
            // create a new list and call permute
            copy(tmparr,permlist,n);
            permute(tmparr,start+1,n);
        }
}
