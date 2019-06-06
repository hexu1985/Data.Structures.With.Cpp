#include <iostream.h>
#include <iomanip.h>
#pragma hdrstop

#include "makesrch.h"    // for function MakeSearch
#include "treescan.h"    // for function Inorder
#include "treeprnt.h"    // for function PrintVTree
#include "bstree.h"      // use BinSTree class


// print an integer value. used by the function Inorder
void PrintInt(int& item)
{
    cout << item << "  ";
}

void main(void)
{
    // declare a tree of integer values
    BinSTree<int> Tree;
    
    // create search tree #1 and print upright with 40 char width
    MakeSearchTree(Tree, 1);
    PrintVTree(Tree.GetRoot(),2,40);

    // inorder scan of the tree visits values in increasing order
    cout << endl << endl << "Sorted List: ";
	 // <int> added due to a bug in Microsoft Visual C++
    Inorder<int> (Tree.GetRoot(),PrintInt);
    cout << endl;


    cout << endl << "Deleting data values 70 and 50." << endl;
    Tree.Delete(70);
    Tree.Delete(50);
    PrintVTree(Tree.GetRoot(),2,40);
    cout << endl;
}

/*
<Run of Program 11.4>

                  50

        20                  70

   10        45        60        90

           30

Sorted List: 10  20  30  45  50  60  70  90

Deleting data values 70 and 50.

                  45

        20                  60

   10        30                  90
*/
