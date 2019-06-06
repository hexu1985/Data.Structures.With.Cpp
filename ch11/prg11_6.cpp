#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#pragma hdrstop

#include "word.h"            // include the Word class
#include "bstree.h"          // include  BinSTree class
#include "treescan.h"        // for Inorder scan

// used by function Inorder
void PrintWord(Word& w)
{
    cout << w;
}

void main(void)
{
    
    // declare a tree of Word objects read from stream fin
    BinSTree<Word> concordTree;
    ifstream fin;
    
    Word w;
    
    // open the file "concord.txt"
    fin.open("concord.txt", ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open \"concord.txt\"\n";
        exit(1);
    }

    // read Word objects from fin until end of file
    while(fin >> w)
    {
        // search for w in the tree
        if (concordTree.Find(w) == 0)
        {
            // w not in tree. update word count and insert word
            w.CountWord();
            concordTree.Insert(w);
        }
        else
        {
            // w in tree. update word count and update word in tree
            w.CountWord();
            concordTree.Update(w);
        }
    }
        
    // print the tree in alphabetical order
	 // <Word> added due to a bug in Microsoft Visual C++
    Inorder<Word> (concordTree.GetRoot(), PrintWord);
}

/*
<File "concord.txt">

Peter Piper picked a peck of pickled peppers. A peck of pickled
peppers Peter Piper picked. If Peter Piper picked a peck of
pickled peppers, where is the peck that Peter Piper picked?

<Run of Program 11.6>

a.......................3: 1  2
if......................1: 2
is......................1: 3
of......................3: 1  2
peck....................4: 1  2  3
peppers.................3: 1  2  3
peter...................4: 1  2  3
picked..................4: 1  2  3
pickled.................3: 1  3
piper...................4: 1  2  3
that....................1: 3
the.....................1: 3
where...................1: 3
*/
