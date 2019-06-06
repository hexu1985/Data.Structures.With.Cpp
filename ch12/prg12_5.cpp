#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "array.h"
#include "arriter.h"

// copy values in one array to another by using their iterators
void Copy(ArrayIterator<int>& Source, ArrayIterator<int>& Dest)
{
    while (!Source.EndOfList())
    {
        Dest.Data() = Source.Data();
        Source.Next();
        Dest.Next();
    }
}

// merge the sorted runs in array A. the first run spans indices
// lowIndex..endOfRun-1 and the second endOfRun..highIndex
void Merge(Array<int>& A,int lowIndex, int endOfRunIndex,
             int highIndex)
{
    // array in which the runs are combined. has same size as In
    Array<int> Out(A.ListSize());

    // left traverses 1st run, right traverses 2nd
    ArrayIterator<int> left(A,lowIndex,endOfRunIndex-1);
    ArrayIterator<int> right(A,endOfRunIndex,highIndex);
    
    // output puts sorted data to Out.
    ArrayIterator<int> output(Out);

    // copy until we hit the end of one or both runs
    while (!left.EndOfList() && !right.EndOfList())
    {
        // if left run data value smaller or equal, assign it to
        // Out. advance to next left run element
        if(left.Data() <= right.Data())
        {
            output.Data() = left.Data();
            left.Next();
        }
        // assign data from right run and advance right
        else
        {
            output.Data() = right.Data();
            right.Next();
        }
        output.Next();	// advance output
    }

    // if one of the runs is not complete, copy it to Out
    if (!left.EndOfList())
        Copy(left,output);
    else if (!right.EndOfList())
        Copy(right,output);

    // reset the iterator for Out and copy from Out to A
    output.Reset();
    
    ArrayIterator<int> final(A);    // use for copying back to A.
    
    Copy(output, final);
}

void main(void)
{
    // array to contain the sorted runs read from stream fin
    Array<int> A(20);
    ifstream fin;
    int i;
    int endOfRun = 0;
    
    // open data file "rundata"
    fin.open("rundata", ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open the file 'rundata'" << endl;
        exit(1);
    }
    
    // read 20 data values in two sorted runs
    fin >> A[0];

    for(i=1;i < 20;i++)
    {
        fin >> A[i];
        if (A[i] < A[i-1])
            endOfRun = i;
    }
    
    // merge runs A[0]..A[endOfRun-1], A[endOfRun]..A[19]
    Merge(A,0,endOfRun,19);
    
    // print the sorted runs, 10 data values per line
    for(i=0;i < 20;i++)
    {
        cout << A[i] << "  ";
        if (i == 9)
            cout << endl;
    }
    cout << endl;
}

/*
<File "rundata">

1 3 6 9 12 23 33 45 55 68 88 95
2 8 12 25 33 48 55 75

<Run of Program 12.5>

1  2  3  6  8  9  12  12  23  25
33  33  45  48  55  55  68  75  88  95
*/
