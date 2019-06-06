#ifndef KEY_VALUE_PAIRS
#define KEY_VALUE_PAIRS

template <class K, class T>
class KeyValue
{           
   protected:
      // key cannot be changed once it is initialized
      const K key;

   public:
      // data is publically accessible
      T value;
      
      KeyValue(K KeyValue, T datavalue);
      
      // assignment operators. do not alter the key member
      KeyValue<K,T>& operator= (const KeyValue<K,T>& rhs);
      
      // comparison operators. based on the two keys
      int operator== (const KeyValue<K,T>& value) const;
      int operator== (const K& keyval) const;
      int operator< (const KeyValue<K,T>& value) const;
      int operator< (const K& keyval) const;
      
      // only public means of accessing the key
      K Key(void) const;
};

template <class K, class T>
KeyValue<K,T>::KeyValue(K KeyValue, T datavalue):
   key(KeyValue), value(datavalue)
{}

template <class K, class T>
KeyValue<K,T>& KeyValue<K,T>::operator=
                              (const KeyValue<K,T>& rhs)
{
   value = rhs.value;
   return *this;
}

template <class K, class T>
int KeyValue<K,T>::operator==
                   (const KeyValue<K,T>& value) const
{
   return key == value.Key();
}

template <class K, class T>
int KeyValue<K,T>::operator== (const K& keyval) const
{
   return key == keyval;
}

template <class K, class T>
int KeyValue<K,T>::operator<
                   (const KeyValue<K,T>& value) const
{
   return key < value.Key();
}

template <class K, class T>
int KeyValue<K,T>::operator< (const K& keyval) const
{
   return key < keyval;
}

template <class K, class T>
K KeyValue<K,T>::Key (void) const
{
   return key;
}

#endif   // KEY_VALUE_PAIRS
