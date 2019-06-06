#ifndef TREE_PRINT
#define TREE_PRINT

#include <iostream.h>
#include <iomanip.h>

#include "treenode.h"
#include "queue.h"

// spacing between levels
const int indentBlock = 6;

// inserts num blanks on the current line
void IndentBlanks(int num)
{
   for(int i = 0;i < num; i++) 
      cout << " ";
}

// print a tree sideways using an RNL tree scan
template <class T>
void PrintTree (TreeNode<T> *t, int level)
{
   // print tree with root t, as long as t != NULL
   if (t != NULL)
   {
      // print right branch of tree t
      PrintTree(t->Right(),level + 1);
      // indent to current level; output node data
      IndentBlanks(indentBlock*level);
      cout << t->data << endl;
      // print left branch of tree t
      PrintTree(t->Left(),level + 1);
   }
}

// record to hold x,y coordinates for a node in PrintVTree
struct Info
{
   int      level, indent;
};

// print tree vertically. dataWidth is max size of data in tree
// blockWidth is user supplied measure of gap between nodes
// on the lowest level of the tree 
template <class T>
void PrintVTree (TreeNode<T> *t, int dataWidth, int screenWidth)
{
  // queues to hold the node and the node print position data
   Queue<TreeNode<T> *> Q;
   Queue<Info> QI;
   
   // variables to hold a node and a node print position
   TreeNode<T> *p;
   Info nodePrintPosition;
   
   // variables holding level and indent of current node
   int nodeLevel, nodeIndent;
   
   // variables holding current level and indent position
   int currPrintLevel = 0, currPrintIndent = 0;

   // posChange is shift on printing line to next node
   // deltpChange is length of movement to left or right
   //  to print a child of the current node
   int posChange, deltaChange, i;
   
   // set x and y print coordinate for the root node     
   nodePrintPosition.level = 0;
   nodePrintPosition.indent = screenWidth/2;
   
   // push root and its print position on the queues
   Q.QInsert(t);           
   QI.QInsert(nodePrintPosition);    
   
   // continue until all nodes have been processed and printed
   while(!Q.QEmpty())
   {
      // delete front node and its print position from the queues    
      p = Q.QDelete();
      nodePrintPosition = QI.QDelete();
      
    
      // get print position. if nodeLevel > current print level
      // add newline and reset print cursor to front of line
      nodeLevel = nodePrintPosition.level;
      nodeIndent = nodePrintPosition.indent;
      if (nodeLevel > currPrintLevel)
      {
       cout << endl << endl;
       currPrintLevel++;
       currPrintIndent = 0;
      }
      
      // before printing data, move cursor to correct location
      // if nodeIndent to right of currPrintIndent, move right
      // posChange - dataWidth spaces; otherwise start at 
      // front of line, shifting posChange-dataWidth spaces; 
      posChange = (nodeIndent > currPrintIndent) ? 
                     nodeIndent - currPrintIndent : nodeIndent;
      for (i = 0; i < posChange-dataWidth; i++)
         cout << " ";
      cout << setw(dataWidth) << p->data;
      
      // update printing pos by using deltaChange to compute 
      // the relative offset to print a child of current node
      currPrintIndent = nodeIndent;

      // 1 << (nodeLevel+2) is 2 ^ (nodeLevel+2);
      deltaChange = screenWidth/(1 << (nodeLevel+2));
      deltaChange = deltaChange < 2 ? 2 : deltaChange;
      
      // look for left child with node and printpos in queue
      if(p->Left() != NULL)
      {
       // set level and indent for the left child
       nodePrintPosition.level = nodeLevel+1;
       nodePrintPosition.indent = nodeIndent - deltaChange;
       Q.QInsert(p->Left());
       QI.QInsert(nodePrintPosition);
      }

      // look for right child with node and printpos in queue
      if(p->Right() != NULL)     // check for right child
      {
       // set level and indent for the left child
       nodePrintPosition.level = nodeLevel+1;
       nodePrintPosition.indent = nodeIndent + deltaChange;
       Q.QInsert(p->Right());
       QI.QInsert(nodePrintPosition);
      }
   }
}

#endif    // TREE_PRINT
