#ifndef ABSTRACT_ITERATOR
#define ABSTRACT_ITERATOR

template <class T>
class Iterator
{
   protected:
      // indicates whether iterator has reached end of list.
      // must be maintained by the derived class
      int iterationComplete;
   
   public:
      // constructor
      Iterator(void);
      
      // required iterator methods
      virtual void Next(void) = 0;
      virtual void Reset(void) = 0;
      
      // data retrieval/modification method
      virtual T& Data(void) = 0;
      
      // test for end of list
      virtual int EndOfList(void) const;
};

// constructor. sets iterationComplete to 0 (False)
template <class T>
Iterator<T>::Iterator(void): iterationComplete(0)
{}

// return the value of iterationComplete.
template <class T>
int Iterator<T>::EndOfList(void) const
{
   return iterationComplete;
}

#endif   // ABSTRACT_ITERATOR