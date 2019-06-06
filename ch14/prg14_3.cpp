#include <iostream.h>
#pragma hdrstop

#include "random.h"
#include "binfile.h"

const long Empty = -1;

// a node that stores a data record in a file
struct FileDataRecord
{
    // data is an integer in this example; in general,
    // the data field is often a complex record
    int data;       
    long nextIndex;  // location of the next record on disk
};

// startindex is index in table. to handle the case where we
// need to update the table, it is passed by reference
void LoadRecord(BinFile<FileDataRecord> &bf, long &startindex,
                FileDataRecord &dr)
{
    // if the table is not empty, startindex points to the head
    // of the list; otherwise startindex is -1
    // bf.Size() locates the next node in the file
    dr.nextIndex = startindex;  
    startindex = bf.Size();

    // append new record in file    
    bf.Append(dr);  
}

// scan a list of nodes in the file and print their data value
void PrintList(BinFile<FileDataRecord> &bf, long startindex)
{
    // index is the first position is the list 
    long index = startindex;
    FileDataRecord rec;
    
    // index moves to end of list (index = -1)
    while (index != Empty)
    {
        // get record; output its value and go to next record
        rec = bf.Read(index);   
        cout << rec.data << "  ";
        index = rec.nextIndex;
    }
    cout << endl;
}

void main(void)
{
    // table of file node indices; hash range is 0 to 9
    long hashTable[10];
    
    // random number generator and a data record    
    RandomNumber rnd;   
    FileDataRecord dr;
    int i, item, request;
    
    // open file "DRfile" with I/O access
    BinFile<FileDataRecord> dataFile("DRfile", INOUT);
    
    // initialize the table to have empty entries
    for(i = 0; i < 10; i++)
        hashTable[i] = Empty;
    
    // enter 50 random integers in the range 0 to 999
    for (i = 0; i < 50; i++)
    {
        item = rnd.Random(1000);
        // initialize and then install the data record      
        dr.data = item;
        LoadRecord(dataFile, hashTable[item % 10],  dr);
    }
    
    // prompt for a hash table index and print the list
    cout << "Enter a hash table index: ";
    cin >> request;
    cout << "Printing entries that hash to " << request << endl;
    PrintList(dataFile, hashTable[request]);
    
    // remove the data file
    dataFile.Delete();
}

/*
<Run of Program 14.3>

Enter a hash table index: 5
Printing entries that hash to 5
835  385  205  185  455  5
*/
