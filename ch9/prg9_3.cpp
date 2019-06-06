#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <iomanip.h>
#pragma hdrstop

#include "node.h"
#include "nodelib.h"
#include "studinfo.h"

void main(void)
{
    Node<StudentRecord> *graduateList=NULL,
                        *currPtr, *prevPtr,
                        *deletedNodePtr;
    StudentRecord srec;
    ifstream fin;

    fin.open("studrecs",ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open file studrecs." << endl;
        exit(1);
    }
    
    // print gpa with one decimal place
    cout.setf(ios::fixed);
    cout.precision(1);
    cout.setf(ios::showpoint);
    
    while(fin >> srec)
    {
        // insert srec at the head of the list
        InsertFront(graduateList,srec);
    }
        
    prevPtr = NULL;                  // prevPtr trails currPtr
    currPtr = graduateList;          // currPtr at start of list
    while (currPtr != NULL)          // traverse to end of list
    {
        if (currPtr->data.gpa < 2.0) // does student graduate?
        {
            if (prevPtr == NULL)     // student at front of list?
            {
                graduateList = currPtr->NextNode();
                deletedNodePtr = currPtr;
                currPtr = graduateList;
            } 
            else    // delete node inside the list
            {
                currPtr = currPtr->NextNode();
                deletedNodePtr = prevPtr->DeleteAfter();
            }
            delete deletedNodePtr;  // remove deleted node
        }
        else
        {
            // no deletion. move on down list
            prevPtr = currPtr;
            currPtr = currPtr->NextNode();
        }
    }
    fin.close();
    
    fin.open("noattend",ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open file noattend." << endl;
        exit(1);
    }
    
    while(srec.name.ReadString(fin) != -1)
        Delete(graduateList,srec);
    
    cout << "Students attending graduation:" << endl;
    PrintList(graduateList,addNewline);
}

/*
<File "studrecs">
Julie Bailey
1.5
Harold Nelson
2.9
Thomas Frazer
3.5
Bailey Harnes
1.7
Sara Miller
3.9
Nancy Barnes
2.5
Rebecca Neeson
4.0
Shannon Johnson
3.8

<File "noattend">
Thomas Frazer
Sara Miller

<Run of Program 9.3>
Students attending graduation:
Shannon Johnson  3.8
Rebecca Neeson  4.0
Nancy Barnes  2.5
Harold Nelson  2.9

*/
