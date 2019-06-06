#ifndef MERGESORT
#define MERGESORT

#include <iostream.h>
#include <stdlib.h>

#include "binfile.h"
#include "arrsort.h"

// scan runs in file fC and alternate their distribution to
// files fA and fB. for the current split, the runs have
// size k*blockSize
template <class T>
void Split(BinFile<T> &fA, BinFile<T> &fB, BinFile<T> &fC,
           int k, int blockSize)
{
   int useA = 1;
   int i = 0;
   int readCount;
   
   // copies to files using block reads and writes
   // of size blockSize
   T *A = new T[blockSize];
   if(A == NULL)
   {
      cerr << "MergeSort: memory allocation failure." << endl;
      exit(1);
   }
   
   // initialize the files before splitting the files
   fA.Clear(); 
   fB.Clear();
   fC.Reset();

   // distribute runs from file fC until end of file
   while (!fC.EndFile())
   {
      // read a block of data into a dynamic array;    
      // readCount is the number of items read
      readCount = fC.Read(A,blockSize);
      
      // if readCount   is 0, we have an end of file
      if (readCount == 0)
         break;
         
      // write block to file fA (if useA is True) or to fB
      if (useA)
         fA.Write(A,readCount);
      else
         fB.Write(A,readCount);
         
      // alternate the file after writing k blocks to the file
      if (++i == k)
      {
         i = 0;
         useA = !useA;
      }
   }
   
   // deallocate the dynamic memory
   delete [] A;
} 
   
// n is current size of a run; copy tail of a run from file fX
// to fY; variable currRunPos is the current index in the run.
template <class T>
void CopyTail(BinFile<T> &fX, BinFile<T> &fY,
              int &currRunPos, int n)
{
   T data;

   // copy each item from current position to end of the run
   while (currRunPos <= n)
   {
      // if no item is read, we have an end of file
      // and hence an end of run
      if (fX.Read(&data, 1) == 0)
         return;
      currRunPos++;
      // update current position and write item to file fY
      fY.Write(&data,1);
   }
}

// merge runs of length n from files fA and fB to file fC   
template <class T>
void Merge (BinFile<T> &fA, BinFile<T> &fB,
            BinFile<T> &fC, int n)
{
   // currA and currB represent the current position in the
   // run in each file
   int currA = 1, currB = 1;
   
   // data items read from fA and fB respectively. haveA/haveB
   // are 1/0 (True or False) to indicate if an item was read
   // from the respective file.
   T dataA, dataB;
   int haveA, haveB;
   
   // initialize the files before the merge begins
   fA.Reset();
   fB.Reset();
   fC.Clear();

   // get an item from each file
   fA.Read(&dataA,1);
   fB.Read(&dataB,1);
   
   for (;;)
   {
      // if dataA <= dataB then copy dataA to fC and update
      // current position in the current run in fA
      if (dataA <= dataB)
      {
         fC.Write(&dataA,1);
         // get next item from fA; if item not found we have
         // end of file and must copy tail of fB to fC; if
         // current position is > n, then we have completed
         // the run in fA and should copy tail of fB 
         if ((haveA = fA.Read(&dataA,1)) == 0 || ++currA > n)
         {
            // copy element from fB that has been read from
            // the stream and update current position in fB
            fC.Write(&dataB,1);
            currB++;
            CopyTail(fB,fC,currB,n);
            
            // size of fA >= size of fB; if at end of fA, done
            if (!haveA)
               break;
            // otherwise in a new run; reset current position 
            currA = 1;
            
            // get next item in B. if none present, we have
            // only one run in A remaining which we must copy
            // to fC. copy the currenly available element from
            // fA before breaking to print tail of fA 
            if ((haveB = fB.Read(&dataB,1)) == 0)
            {
               fC.Write(&dataA,1);
               currA = 2;
               break;
            }
            // otherwise set current position in run in fB
            currB = 1;
         }
      }
      else
      {
         // copy dataB to fC and update current position in fB
         fC.Write(&dataB,1);
         
         // check for end of run or end of file in fB
         if ((haveB = fB.Read(&dataB,1)) == 0 || ++currB > n)
         {
            // if end occurs, write item that is already read
            // from fA, update its position and then write the
            // tail of the run 
            fC.Write(&dataA,1);
            currA++;
            CopyTail(fA,fC,currA,n);
            // if no more items in fB, set current position in
            // fA and prepare to copy the last run in fA
            if (!haveB)
            {
               currA = 1;
               break;
            }
            
            // otherwise, set current position in fB and get
            // an item from fA
            currB = 1;
            if ((haveA = fA.Read(&dataA,1)) == 0)
               break;
            currA = 1;
         }
      }
   }
   
   // this copies the tail of the last run in fA if it exists
   if(haveA && !haveB)
      CopyTail(fA,fC,currA,n);
}


// function to sort file fC using runs which are multiples of
// blockSize. initially blocks of data are read, sorted using
// QuickSort and then written as runs to separate temporary
// files fA and fB 
template <class T>   
void MergeSort(BinFile<T> &fC, int blockSize)
{
   // temporary file to split the runs from fC
   BinFile<T> fA("fileA", INOUT); 
   BinFile<T> fB("fileB", INOUT);
   
   // the total size of the file and the blockSize
   int size = int(fC.Size()), n = blockSize;
   int k = 1, useA = 1, readCount;
   T *A; 
   
   // reset file pointer for fC to the front of the file
   fC.Reset();
   
   
   // for small file, read data from fC, sort, and copy back
   if (size <= blockSize)
   {
      // allocate a buffer to hold the data and do a block
      // read of the data
      A = new T[size];
      if (A == NULL)
      {
         cerr << "MergeSort: memory allocation failure." << endl;
         exit(1);
      }
      fC.Read(A,size);
      
      // sort it using a fast internal sort method
      QuickSort(A,0,(int)size-1);
      
      // clear the file and rewrite the sorted data
      fC.Clear();
      fC.Write(A,size);
      
      // deallocate the buffer and return 
      delete [] A;
      return;
   }
   else
   {
      // allocate the buffer and read blocks to end of file 
      A = new T[blockSize];
      if(A == NULL)
      {
         cerr << "MergeSort: memory allocation failure." << endl;
         exit(1);
      }
      while (!fC.EndFile())
      {
         readCount = fC.Read(A,blockSize);
         if (readCount == 0)
            break;
            
         // sort the block and then alternalte writing the run
         // to fA and fB
         QuickSort(A,0,readCount-1);
         if (useA)
            fA.Write(A,readCount);
         else
            fB.Write(A,readCount);
         useA = !useA;
      }
      delete [] A;
   }
   
   // merge split files back to fC with runs of size blockSize
      
   Merge(fA, fB, fC, blockSize);
   
   // double the size of the current sorted runs
   k *= 2;
   n = k * blockSize;
   
   // when n is >= the size of the file, fC has one run
   // and is sorted 
   while (n < size)
   {
      // on each pass, split the runs; remerge into runs of
      // double the length
      Split(fA, fB, fC, k, blockSize);
      Merge(fA, fB, fC, n);
      k *= 2;
      n = k * blockSize;
   }
   
   // remove the temporary files
   fA.Delete();
   fB.Delete();
}  

#endif // MERGESORT
