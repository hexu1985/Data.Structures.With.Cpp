#include <iostream.h>
#pragma hdrstop

#include "random.h"         // provides a random number generator

typedef int DataType;       // form queues of integers

#include "aqueue.h"

// user type distinguishes ones and tens digit of a number
enum DigitKind {ones,tens};

// distribute the array of elements into one of 10 queues with
// indices 0-9. user defined type DigitKind indicates whether the
// distribution uses the ones or tens digit of the number to
// place the element in the queue
void Distribute(int L[],Queue digitQueue[],int n,
                DigitKind kind)
{
    int i;

    // loop through the n element array
    for (i = 0; i < n; i++)
        if (kind == ones)
            // compute the ones digit and use as queue index
            digitQueue[L[i] % 10].QInsert(L[i]);
        else
            // compute the tens digit and use as queue index
            digitQueue[L[i] / 10].QInsert(L[i]);
}       

// gather elements from the queues and copy back to array
void Collect(Queue digitQueue[], int L[])
{
    int i = 0, digit = 0;

    // scan the array of queues using indices 0, 1, 2, etc.
    for (digit = 0; digit < 10; digit++)
        // collect items until queue empty and copy items back
        // to the array
        while (!digitQueue[digit].QEmpty())
            L[i++] = digitQueue[digit].QDelete();
}

// scan the n element array and print each item.
// separate items into rows of 10
void PrintArray(int L[],int n)
{
    int i = 0;

    while(i < n)
    {
        cout.width(5);              // print width 5 spaces
        cout << L[i];               // print element
        if (++i % 10 == 0)          // newline every 10 numbers
            cout << endl;
    }
    cout << endl;
}

void main(void)
{
    // 10 queues that act as bins to collect the numbers
    Queue digitQueue[10];
    
    // array of 50 integers
    int L[50];
    
    int i = 0;
    RandomNumber rnd;               // provides random numbers
    
    // initialize array with 50 random numbers in range 0 - 99
    for (i = 0; i < 50; i++)
        L[i] = rnd.Random(100);                     

    // distribute by ones digit into 10 bins; collect and print
    Distribute(L, digitQueue, 50, ones);
    Collect(digitQueue, L);
    PrintArray(L,50);

    // distribute by tens digit into 10 bins; collect and print
    // the sorted array
    Distribute(L,digitQueue, 50, tens);
    Collect(digitQueue,L);
    PrintArray(L,50); 
}

/*
<Run of Program 5.5>

   40   70   20   51   11   81   21   12   52   92
   62   72   82   82   62   72   52   83   63   23
    3   73   33   54   24   84   55   15   65   85
   25   16   46   86   36   67   17   27    7   97
   88   98   68   69   79   89   29   69   99   59

    3    7   11   12   15   16   17   20   21   23
   24   25   27   29   33   36   40   46   51   52
   52   54   55   59   62   62   63   65   67   68
   69   69   70   72   72   73   79   81   82   82
   83   84   85   86   88   89   92   97   98   99

*/
