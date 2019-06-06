#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS

#include "keyval.h"
#include "bstree.h"
#include "treeiter.h"

template <class K, class T>
class Dictionary: public BinSTree< KeyValue<K,T> >
{
   // default value for creation of a dictionary entry.
   // used by index operator, InDictionary, and DeleteKey
   private:
      T defaultValue;

   public:
      // constructor
      Dictionary(const T& defval);
      
      // index operator.
      T& operator[] (const K& index);
      
      // additional dictionary methods
      int InDictionary(const K& keyval);
      void DeleteKey(const K& keyval);
};

// constructor. initialize base class and defaultValue
template <class K, class T>
Dictionary<K,T>::Dictionary(const T& defaultval):
      BinSTree< KeyValue<K,T> >(), defaultValue(defaultval)
{}

// index operator. here is where most of the work is done
template <class K, class T>
T& Dictionary<K,T>::operator[] (const K& index)
{
   // define a target KeyValue object with the default value
   KeyValue<K,T> targetKey(index,defaultValue);

   // search for key. if not found, insert targetKey
   if(!Find(targetKey))
      Insert(targetKey);
      
   // return reference to data value found or inserted.
   // current is maintained by the BinSTree class
   return current->data.value;
}

// see if KeyValue object exists with given key
template <class K, class T>
int Dictionary<K,T>::InDictionary(const K& keyval)
{
   // define a target KeyValue object with the default value
   KeyValue<K,T> tmp(keyval,defaultValue);
   int retval = 1;
   
   // search for tmp in the tree and return the result
   if(!Find(tmp))
      retval = 0;
   return retval;
}

// delete the KeyValue object with given key from dictionary
template <class K, class T>
void Dictionary<K,T>::DeleteKey(const K& keyval)
{     
   KeyValue<K,T> tmp(keyval,defaultValue);
   
   Delete(tmp);
}

template <class K, class T>
class DictionaryIterator:
                        public InorderIterator< KeyValue<K,T> >
{
   public:
      // constructor
      DictionaryIterator(Dictionary<K,T>& dict);
      
      // begin iteration of a new dictionary
      void SetList(Dictionary<K,T>& dict);
};

// constructor. dict "is a" BinSTree object. just use
// its public method GetRoot to initialize the
// InorderIterator base class
template <class K, class T>
DictionaryIterator<K,T>::DictionaryIterator
                         (Dictionary<K,T>& dict):
             InorderIterator< KeyValue<K,T> >(dict.GetRoot())
{}

// use the base class method SetTree
template <class K, class T>
void DictionaryIterator<K,T>::SetList(Dictionary<K,T> & dict)
{
   SetTree(dict.GetRoot());
}

#endif   // DICTIONARY_CLASS
