#include <iostream.h>
#pragma hdrstop

// include TreeNode class and library of treenode functions
#include "treenode.h"
#include "treelib.h"

void main(void)
{
    TreeNode<char> *root;

    // use the character Tree_2 
    MakeCharTree(root, 2);
    
    // variable that is updated by CountLeaf
    int leafCount = 0;

    // make call to CountLeaf function. get total leafcount   
    CountLeaf(root, leafCount);
    cout << "Number of leaf nodes is " << leafCount << endl;
    
    // make call to Depth function and print depth of tree
    cout << "The depth of the tree is "
         << Depth(root) << endl;
}

/*
<Run of Program 11.1>

Number of leaf nodes is 4
The depth of the tree is 3

*/
