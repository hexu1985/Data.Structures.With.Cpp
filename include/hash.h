#ifndef HASH_TABLE_CLASS
#define HASH_TABLE_CLASS

#include "array.h"
#include "list.h"
#include "link.h"
#include "iterator.h"

template <class T>
class HashTableIterator;

template <class T>
class HashTable: public List<T>
{
   protected:
      // number of buckets; represents size of the hash table
      int numBuckets; 
      
      // the hash table is an array of linked lists
      Array< LinkedList<T> > buckets;
      
      // the hash function and addr of last data item accessed
      unsigned long (*hf)(T key);
      T *current;

   public:
      // constructor with parameters including size of hash
      // table and the hash function
      HashTable(int nbuckets, unsigned long hashf(T key));
      
      // list handling methods
      virtual void Insert(const T& key);
      virtual int Find(T& key);
      virtual void Delete(const T& key);
      virtual void ClearList(void);
      void Update(const T& key);
      
      // associated iterator has access to the data members
      friend class HashTableIterator<T>;
};

template <class T>
HashTable<T>::HashTable(int nbuckets,
                        unsigned long hashf(T key)):
          List<T>(), numBuckets(nbuckets),
          buckets(numBuckets), hf(hashf), current(NULL)
{}

template <class T>
void HashTable<T>::Insert(const T& key)
{
   // hashval is the bucket number (index of the linked list)
   int hashval = int(hf(key) % numBuckets);
   
   // lst is an alias for buckets[hashval]. avoids indexing.
   LinkedList<T>& lst = buckets[hashval];
   
   for(lst.Reset();!lst.EndOfList();lst.Next())
      // if match key, update data and return
      if (lst.Data() == key)
      {
         lst.Data() = key;
         current = &lst.Data();
         return;
      }
   // data corresponding to key is not found. add item to list
   lst.InsertRear(key);
   current = &lst.Data();
   size++;
}

template <class T>
int HashTable<T>::Find(T& key)
{
   // compute the hash value and set lst to point at its
   // corresponding  LinkedList
   int hashval = int(hf(key) % numBuckets);
   LinkedList<T>& lst = buckets[hashval];
   
   // scan nodes in linked list looking for a match with key
   for(lst.Reset();!lst.EndOfList();lst.Next())
      // if match occurs, get data value, set current. return
      if (lst.Data() == key) 
      {
         key = lst.Data();
         current = &lst.Data();
         return 1;               // return True
      }
   return 0;                     // otherwise, return False
}

template <class T>
void HashTable<T>::Delete(const T& key)
{
   int hashval = int(hf(key) % numBuckets);
   LinkedList<T>& lst = buckets[hashval];
   
   for(lst.Reset();!lst.EndOfList();lst.Next())
      if (lst.Data() == key)  // if match key, delete node
      {
         lst.DeleteAt();
         current = &lst.Data();
         size--;
         return;
      }
}

template <class T>
void HashTable<T>::ClearList(void)
{     
   for(int i=0;i < numBuckets;i++)
      buckets[i].ClearList();
   size = 0;
   current = NULL;
}

template <class T>
void HashTable<T>::Update(const T& key)
{     
   if (current != NULL && *current == key)
         *current = key;
   else
      Insert(key);
}

template <class T>
class HashTableIterator: public Iterator<T>
{
   private:
      // points to the hash table that must be traversed
      HashTable<T> *hashTable;
      
      // index of current bucket being traversed and a
      // pointer to the linked list
      int currentBucket;
      LinkedList<T> *currBucketPtr;
      
      // utility to implement Next()
      void SearchNextNode(int cb);
   public:
      // constructor
      HashTableIterator(HashTable<T>& ht);

      // basic iterator methods
      virtual void Next(void);
      virtual void Reset(void);
      virtual T& Data(void);

      // arrange for the iterator to traverse another table
      void SetList(HashTable<T>& lst);
};

// beginning at index cb, look for the next non-empty
// list to scan
template <class T>
void HashTableIterator<T>::SearchNextNode(int cb)
{
   currentBucket = -1;
   
   // if index cb > table size, terminate search; scan is over
   if (cb > hashTable->numBuckets)
      return;
      
   // otherwise search from current list to end of table
   // for a non-empty bucket and update private data members
   for(int i=cb;i < hashTable->numBuckets;i++)
      if (!hashTable->buckets[i].ListEmpty())
      {
         // before return, set currentBucket index to i and
         // set currBucketPtr to the new non-empty list. 
         currBucketPtr = &hashTable->buckets[i];
         currBucketPtr->Reset();
         currentBucket = i;
         return;
      }
}

// constructor; initialize both the base class
// and hashTable. SearchNextNode identifies
// the first non-empty bucket in the table   
template <class T>
HashTableIterator<T>::HashTableIterator(HashTable<T>& ht):
   Iterator<T>(), hashTable(&ht)
{
   SearchNextNode(0);
}

// move to the next data item in the table
template <class T>
void HashTableIterator<T>::Next(void)
{
   // using current list, move to next node or end of list
   currBucketPtr->Next();
   
   // at end of list, call SearchNextNode to identify next 
   // non-empty bucket in the table
   if (currBucketPtr->EndOfList())
      SearchNextNode(++currentBucket);
      
   // set the iterationComplete flag to check if currentBucket 
   // index is at end of list, 
   iterationComplete = currentBucket == -1;
}

template <class T>
void HashTableIterator<T>::Reset(void)
{
   iterationComplete = hashTable->ListEmpty();
   SearchNextNode(0);
}

template <class T>
T& HashTableIterator<T>::Data(void)
{
   return (*currBucketPtr).Data();
}

template <class T>
void HashTableIterator<T>::SetList(HashTable<T>& lst)
{
   hashTable = &lst;
   Reset();
}
   
#endif   // HASH_TABLE_CLASS
