// record containing a string and its frequency
struct NameRecord
{
   String name;
   int count;
};

// function for use by the Hash class
unsigned long hash(NameRecord elem)
{
   unsigned long hashval = 0;

   // shift hashval left three bits and add in next character
   for(int i=0;i< elem.name.Length();i++)
      hashval = (hashval << 3) + elem.name[i];
   return hashval;
}

// Hash class requires "==" for NameRecord
int operator== (const NameRecord& x, const NameRecord& y)
{
   return x.name == y.name;
}
