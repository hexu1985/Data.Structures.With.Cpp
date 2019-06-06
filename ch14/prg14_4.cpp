
#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

#include "binfile.h"
#include "merge.h"
#include "random.h"

// print the elements from BinFile f in rows of 9 items each
void PrintFile (BinFile<int> &f, long n)
{
    int data;
	long i;

    // initialize n to the size of the file
    n = (f.Size() < n) ? f.Size() : n;  

    // reset the file pointer to front of the file
    f.Reset(); 

    // use a sequential scan of the file, read each element and
    // print its value.  separate each 9 elements with a newline
    for(i = 0; i < n; i++)
    {
        if (i % 9 == 0)
            cout << endl;
        f.Read(&data, 1);
        cout << setw(5) << data << "  ";
    }
    cout << endl;
}

// create a file with n random integers in the range 0 to 32767
void  LoadFile(BinFile<int> &f, int n)
{
   int i, item;
   RandomNumber rnd;

    // reset file
    f.Reset();
   
    // load the file with n random numbers
    for (i = 0; i < n; i++)
    {
        item = rnd.Random(32768L);
        f.Write(&item,1);
    }
}

void main(void)
{
    // fC is initialized with random data and sorted
    BinFile<int> fC("fileC", INOUT);

    // create a file with 1000 random integer values
    LoadFile(fC,1000);

    // print the first 45 elements of the initial list
    cout << "First 45 elements of the data file:" << endl;
    PrintFile(fC,45);
    cout << endl;

    // execute the merge sort
    MergeSort(fC, 100);

    // print the first 45 elements of the sorted list
    cout << "First 45 elements of the sorted data file:"
		 << endl;
    PrintFile(fC,45);
    
    // remove the file
    fC.Delete();
}

/*
<Run of Program 14.4>

First 45 elements of the data file:

14879  26060  28442  20710  19366  10959  17112   7880  22963
16103  22910   6789   4976  19024   1470  25654  31721  28709
  997  23378  14186  14986  21650   7351  25237  28059   5942
 9593  20294  27928   8267   9837  17191   8398  18261  21620
 5139    964  10393  16777  15915  18986  22175   2697  20409

First 45 elements of the sorted data file:

   19     76     94     98    106    119    188    192    236
  259    308    344    346    371    383    424    463    558
  570    605    614    714    741    756    794    861    864
  891    910    923    964    979    997   1000   1007   1029
 1051   1079   1112   1223   1232   1347   1470   1515   1558
*/
