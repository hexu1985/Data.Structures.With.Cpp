#include <iostream.h>
#pragma hdrstop

#include "bstree.h"
#include "avltree.h"
#include "random.h"

// loads array, binary search tree and avl tree with same 
// n random numbers in the range 0 - 999  
void SetupLists( BinSTree<int> &Tree1, AVLTree<int> &Tree2,
                 int A[], int n)
{
    int i;
    RandomNumber rnd;
    
    // store random number in array A and use value to 
    // insert a new node in binary search and avl trees    
    for (i = 0; i < n; i++)
    {
        A[i] = rnd.Random(1000);
        Tree1.Insert(A[i]);
        Tree2.Insert(A[i]);
    }
}

// searching for item in tree t.  add to accumulated total
// the length of path from root to the value
template <class T>
void PathLength(TreeNode<T> *t, long &totallength, int item)
{
    // once item is found or if item is not in the list, return.
    // the length of the path has been determined
    if (t == NULL || t->data == item)
        return;
    else
    {
        // moving to the next level;  increment total length
        totallength++;
        if (item < t->data)
            PathLength(t->Left(), totallength, item);
        else
            PathLength(t->Right(), totallength, item);
    }
}

void main(void)
{
    // variables for trees and array
    BinSTree<int>   binTree;
    AVLTree<int>    avlTree;
    int   *A;
    
    // total length of searchs to find items from array A in
    // bintree and avltree 
    long totalLengthBintree = 0, totalLengthAVLTree = 0;
    int n,i;
    
    cout << "How many nodes do you want in the trees? ";
    cin >> n;
    
    // setup the lists for the array and the trees
    A = new int[n];
    SetupLists(binTree,avlTree,A,n);
    
    for (i = 0; i < n; i++)
    {
        PathLength(binTree.GetRoot(), totalLengthBintree, A[i]);
        PathLength((TreeNode<int> *)avlTree.GetRoot(),
                    totalLengthAVLTree, A[i]);
    }
    
    cout    << "Average search for BinSTree is " 
            << float(totalLengthBintree)/n << endl;
    cout    << "Average search for AVLTree is " 
            << float(totalLengthAVLTree)/n << endl;
}

/*

<Run #1 of Program 13.4>

How many nodes do you want in the trees? 1000
Average search for BinSTree is 9.073
Average search for AVLTree is 7.525

<Run #2 of Program 13.4>

How many nodes do you want in the trees? 10000
Average search for BinSTree is 11.8558
Average search for AVLTree is 8.7608
*/

