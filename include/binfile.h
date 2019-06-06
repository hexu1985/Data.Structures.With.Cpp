#ifndef BINARY_FILE_CLASS
#define BINARY_FILE_CLASS

// system files containing hierarchy of file handling methods.
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

#include "strclass.h"

// file access types
enum Access  {IN, OUT, INOUT};
// type of seeks that can be performed
enum SeekType {BEG,CUR,END};

template <class T>
class BinFile 
{
   private:
	  // C++ file stream object with its access type and name
	  fstream f;
      Access accessType;   // file access type
      String fname;        // physical file name

      int fileOpen;        // is the file open?

      // parameters measuring file as direct access structure
      int Tsize;           // size of a data record
      long fileSize;       // number of file records

      // prints an error message and terminates the program
      void Error(char *msg);  
      
   public:
      // constructors and destructor
      BinFile(const String& fileName, Access atype = OUT);
      ~BinFile(void);

      // copy constructor. an object must be passed by
      // reference. terminates the program
      BinFile(BinFile<T>& bf);


      // file utility methods    
      void Clear(void);    // truncate records in the file
      void Delete(void);   // close file and remove it
      void Close(void);    // close the file
      int EndFile();       // tests EOF condition  
      long Size();         // returns number of file records
      void Reset(void);    // reset the file to first record
      // locate file pointer pos records from beginning,
      // current location or end of the file
      long Seek(long pos, SeekType mode);
	    
      // block read of n data values into address A
      int  Read(T *A, int n);
      // block write of n data values from address A  
      void Write(T *A, int n);
      // value of record at current location
      T Peek(void);
      
      // copy data to record at index pos
      void Write (const T& data, long pos);
      // read record from index pos
      T Read (long pos);
      // write a record at end of the file
      void Append(T item);
};

template <class T>
void BinFile<T>::Error(char *msg)
{
   cerr << msg << endl;
   exit(1);
}

// constructor; opens file with given file name and access
template <class T>
BinFile<T>::BinFile(const String& fileName, Access atype)
{
   // stream open operation includes access type; for IN, a 
   // file is not created if does not exist; for OUT, any
   // existing data are thrown away (truncated); for INOUT,
   // the file has input and output capability  
   if (atype == IN)
#ifdef __THINKC__
      f.open(fileName, ios::in | ios::nocreate);
#else
      f.open(fileName, ios::in | ios::nocreate | ios::binary);
#endif // __THINKC__
   else if (atype == OUT)
#ifdef __THINKC__
      f.open(fileName, ios::out | ios::trunc);
#else
      f.open(fileName, ios::out | ios::trunc | ios::binary);
#endif // __THINKC__
   else
#ifdef __THINKC__
      f.open(fileName, ios::in | ios::out);
#else
      f.open(fileName, ios::in | ios::out | ios::binary);
#endif // __THINKC__
   if(!f)
      Error("BinFile constructor: file cannot be opened");
   else
      fileOpen = 1;
      
   accessType = atype;

   // compute the number of records in the file
   
   // Tsize is the number of bytes in the data type
   Tsize = sizeof(T);
   if (accessType == IN || accessType == INOUT)
   {
      // compute number of records in an input file by seeking
      // to the end of the file, calling tellg to obtain the
      // file size in bytes, and then dividing by the data
      // size. reset to the beginning of the file
      f.seekg(0,ios::end);
      fileSize = f.tellg()/Tsize;
      f.seekg(0,ios::beg);
   }
   else
      fileSize = 0;   // size is 0 for OUT files

   // record physical file name in fname
   fname = fileName;
}

// avoid warning message that parm bf not referenced
#pragma warn -par

// copy constructor. terminates program if client initializes
// a BinFile object, passes one by value or returns one
// as the value of a function
template <class T>
BinFile<T>::BinFile(BinFile<T>& bf)
{
   Error("Pass file parameter by reference only");
}  

// destructor. close the file.
template <class T>
BinFile<T>::~BinFile(void)
{
   if(fileOpen)
   {
      f.close();
      fileOpen = 0;
   }
}

template <class T>
void BinFile<T>::Reset(void)
{
   if(!fileOpen)
      Error("BinFile Reset: file closed");
      
   if (accessType == OUT)
      f.seekp(0,ios::beg);
   else
      f.seekg(0,ios::beg);
}

// seek pos records from beginning, current location or end
// of the file
template <class T>
long BinFile<T>::Seek(long pos, SeekType mode)
{
   // the seekg or seekp param
   ios::seek_dir fromWhere;
   long retval;
   
   if(!fileOpen)
      Error("BinFile Seek: file closed");

   // assign fromWhere according to mode
   switch(mode)
   {
      case BEG:
	       fromWhere = ios::beg;
	       break;
      case CUR:
	       fromWhere = ios::cur;
	       break;
      case END:
	       fromWhere = ios::end;
	       break;
   }
   if (accessType == OUT)
   {
      f.seekp(pos*Tsize,fromWhere);
      retval = f.tellp();
   }
   else
   {
      f.seekg(pos*Tsize,fromWhere);
      retval = f.tellg();
   }
   return retval;
}

// Clear deletes file records by closing and then opening file
template <class T>
void BinFile<T>::Clear(void)
{
   if (!fileOpen)
		Error("BinFile Clear: file closed");
   // an 'IN' file cannot be cleared
   if (accessType == IN)
      Error("Invalid file access operation");

   // close and then open the file
   f.close();
   if (accessType == OUT)
#ifdef __THINKC__
      f.open(fname, ios::out | ios::trunc);
#else
      f.open(fname, ios::out | ios::trunc | ios::binary);
#endif // __THINKC__
   else
#ifdef __THINKC__
      f.open(fname, ios::in | ios::out | ios::trunc);
#else
      f.open(fname, ios::in | ios::out | ios::trunc | ios::binary);
#endif // __THINKC__
   if (!f)
      Error("BinFile Clear: cannot reopen the file");
      
   fileSize = 0;
}

#ifdef __THINKC__
#include <unix.h>
#endif   // __THINKC__

#ifdef __BORLANDC__
#include <io.h>
#endif   // __BORLANDC__

#ifdef __GNUC__
#include <unistd.h>
#endif   // __GNUC__

// Delete closes file and removes it from the file system
template <class T>
void BinFile<T>::Delete(void)
{
   if (!fileOpen)
	  Error("BinFile Delete: file closed");

   // close the file
   f.close();
   fileOpen = 0;
   
   // remove it from the file system
   unlink(fname);
}

template <class T>
long BinFile<T>::Size(void)
{
   if(!fileOpen)
      Error("BinFile Size: file closed");
   return fileSize;
}

template <class T>
int BinFile<T>::EndFile(void)
{
   if(!fileOpen)
      Error("BinFile EndFile: file closed");

   return f.eof();
}

template <class T>
void BinFile<T>::Write (const T& data, long pos)
{
   if(!fileOpen)
      Error("BinFile Write(T data,int pos): file closed");

   if (accessType == IN)
      Error("Invalid file access operation");
   else if (pos < 0)
      Error ("Invalid file access operation"); 
   f.seekp(pos*Tsize, ios::beg);
   f.write((char *)&data,Tsize);
   f.seekg(0,ios::end);
   fileSize = f.tellg()/Tsize;
   f.seekg(pos*Tsize,ios::beg);
}

template <class T>
void BinFile<T>::Append(T data)
{
   if(!fileOpen)
      Error("BinFile Append: file closed");

   if (accessType == IN)
      Error("Invalid file access operation");
   if (accessType == OUT)
		f.seekp(0, ios::end);
   else
		f.seekg(0, ios::end);
   f.write((char *)&data,Tsize);
   fileSize++;
}

// Read returns the data at record pos in the file
template <class T>
T BinFile<T>::Read (long pos)
{
   // variable to hold the data item
   T data;

   if(!fileOpen)
      Error("BinFile Read(int pos): file closed");

   // the Read method is invalid with an 'OUT' only file
   if (accessType == OUT)
      Error("Invalid file access operation");
   // test for valid pos in range 0 to fileSize-1
   else if (pos < 0 || pos >= fileSize)
      Error("Invalid file access operation");

   // position the current file pointer and extract data
   // using the fstream read method
   f.seekg(pos*Tsize, ios::beg);
   f.read((char *)&data,Tsize);
   
   // if the access mode is IN and we have read all records,
   // set the stream eof bit
   if (accessType == IN)
      if (f.tellg()/Tsize >= fileSize)
	  // sets the eof bit
	  f.clear(ios::eofbit);
      
   return data;
}

template <class T>
T BinFile<T>::Peek (void)
{
   T data;
   
   if(!fileOpen)
      Error("BinFile Peek: file closed");

   if (accessType == OUT)
      Error("Invalid file access operation");
   else if (fileSize == 0)
      Error("File is empty");
   f.read((char *)&data,Tsize);
   f.seekg(-Tsize, ios::cur);
   return data;
}

template <class T>
int BinFile<T>::Read(T *A, int n)
{
   long currpos;
   int nread;

   if (accessType == OUT)
      Error("Invalid file access operation");
   else if (n < 0) 
      Error("Invalid record count");
   
   if(!fileOpen)
      Error("BinFile Read(T *A, int n): file closed");

   currpos = f.tellg()/Tsize;
   if (n == 0 || currpos == fileSize)
      return 0;
      
   nread = int((currpos+n <= fileSize) ? n : fileSize-currpos);
   f.read((char *)A, nread*Tsize);
   
   // if the access mode is IN and we have read all records,
   // set the stream eof bit
   if (accessType == IN)
      if (f.tellg()/Tsize >= fileSize)
	 // used this way, clear actually sets eofbit
	 f.clear(ios::eofbit);
      
   return nread;
}

// writes an n-element list from array A to the file     
template <class T>
void BinFile<T>::Write(T *A, int n)
{
   long previousRecords;

   // Write is an invalid operation with an 'IN' only file 
   if (accessType == IN)
      Error("Invalid file access operation");
   
   if(!fileOpen)
      Error("BinFile Write(T *A, int n): file closed");

   // compute the new file size. call tellg to compute number
   // of file records prior to output point. determine if
   // file size will expand. if so, increment fileSize by
   // the number of records that will be added
   previousRecords = f.tellp()/Tsize;
   if (previousRecords + n > fileSize)
      fileSize += previousRecords + n - fileSize;

   // the number of bytes to write is n * Tsize; 
   f.write((char *)A,Tsize*n);
}

template <class T>
void BinFile<T>::Close(void)
{
   if (!fileOpen)
	  Error("BinFile Close: file closed");

   f.close();
   fileOpen = 0;
}

#endif   // BINARY_FILE_CLASS
