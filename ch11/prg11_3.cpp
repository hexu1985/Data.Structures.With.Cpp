#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

// include PrintVTree from the library
#include "treelib.h"
#include "treeprnt.h"


void main(void)
{
    // declare a character tree
    TreeNode<char> *root;
    
    // assign Tree_2 to root
    MakeCharTree(root, 2);

    cout << "Print tree on a 30 character screen" << endl;
    PrintVTree(root,1, 30);
    cout << endl << endl;
    
    cout << "Print tree on a 60 character screen" << endl;
    PrintVTree(root,1, 60);
	 cout << endl;
}

/*
<Run of Program 11.3>

Print tree on a 30 character screen
              A

       B             C

    D             E     F

      G         H   I

Print tree on a 60 character screen
                             A

              B                             C

       D                             E             F

          G                       H     I

*/
