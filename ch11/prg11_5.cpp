#include <iostream.h>
#pragma hdrstop

#include "random.h"          // generate random integers
#include "bstree.h"          // include BinSTree class
#include "treescan.h"        // for function Inorder
#include "intcount.h"        // defines IntegerCount record

// called by Inorder to print an IntegerCount record
void PrintNumber(IntegerCount& N)
{
    cout << N.number << ':' << N.count << endl;
}

void main(void)
{
    // declare a tree of IntegerCount record values
    BinSTree<IntegerCount> Tree;
    
    long n;
    IntegerCount N;
    RandomNumber rnd;

    // generate 100000 random integers in range 0..9
    for(n=0;n < 100000L;n++)
    {
        // generate an IntegerCount record with a random key
        N.number = rnd.Random(10);
        
        // search for the key in the tree.
        if (Tree.Find(N))
        {
            // key found, increment count and update
            N.count++;
            Tree.Update(N);
        }
        else
        {

            // when int first appears, insert with count field 1.
            N.count = 1;
            Tree.Insert(N);
        }
    }
    
    // inorder scan outputs records in order by key field
	 // <IntegerCount> added due to a bug in Microsoft Visual C++
    Inorder<IntegerCount> (Tree.GetRoot(),PrintNumber);
}

/*
<Run of Program 11.5>

0:10116
1:9835
2:9826
3:10028
4:10015
5:9975
6:9983
7:10112
8:10082
9:10028
*/
