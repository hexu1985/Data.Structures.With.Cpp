#include <iostream.h>
#include <ctype.h>
#include <stdlib.h>
#pragma hdrstop

#include "treescan.h"
#include "treelib.h"
#include "treeprnt.h"

// used to lowercase char data values during postorder scan
void LowerCase(char &ch)
{
    ch = tolower(ch);
}

void main(void)
{
    // pointers for original and copied tree
    TreeNode<char> *root1, *root2;
    
    // create Tree_0 and print it
    MakeCharTree(root1, 0);
    PrintTree (root1, 0);
    
    // copy the tree so root is root2
    cout << endl << "Copy:" << endl;
    root2 = CopyTree(root1);
    
    // do postorder scan and then print tree.
	 // <char> added due to a bug in Microsoft Visual C++
    Postorder<char> (root2,LowerCase);
    PrintTree (root2, 0);
}

/*
<Run of Program 11.2>

      C
            E
A
            D
      B

Copy:
      c
            e
a
            d
      b
*/
