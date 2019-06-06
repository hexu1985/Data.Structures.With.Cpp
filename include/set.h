#ifndef SET_CLASS
#define SET_CLASS

#include <iostream.h>
#include <stdlib.h>

enum ErrorType
{
    InvalidMember, ExpectRightBrace, MissingValue,
    MissingComma, InvalidChar, MissingLeftBrace,
    InvalidInputData, EndOfFile, OutOfMemory,
    InvalidMemberRef, SetsDifferentSize
};

template <class T>
class Set 
{
    private:
        // max number of elements in the set
        int setrange;
        
        // number of bytes in bit array and the array pointer
        int arraysize;
        unsigned short *member;
        
        // fatal error utility function
        void Error(ErrorType n) const;
        
        // implement the mapping of set elements to bits
        // within 16-bit short integers
        int ArrayIndex(const T& elt) const;
        unsigned short BitMask(const T& elt) const;
    
    public:
        // constructor. create an empty set
        Set(int setrange);
        
        // copy constructor
        Set(const Set<T>& x);
        
        // destructor
        ~Set(void);
        
        // assignment operator
        Set<T>& operator= (const Set<T>& rhs);
               
        // element membership
        int IsMember(const T& elt);

        // set equality
        int operator== (const Set<T>& x) const;

        // set union
        Set operator+ (const Set<T>& x) const;
        // set intersection
        Set operator* (const Set<T>& x) const;
        
        // set insertion/deletion operations
        void Insert(const T& elt);
        void Delete(const T& elt);

        // Set stream I/O operators
        friend istream& operator>> (istream& istr,
                                    Set<T>& x);             
        friend ostream& operator<< (ostream& ostr,
                                    const Set<T>& x);
};

template <class T>
void Set<T>::Error (ErrorType n) const
{
    cout << endl;
    switch(n)
    {
        case InvalidMember:     
                    cerr << "Invalid set member";
                    break;
        case ExpectRightBrace:  
                    cerr << "Expect right brace '}'";
                    break;
        case MissingValue:      
                    cerr << "Missing a value after a comma";
                    break;
        case MissingComma:      
                    cerr << "Separate members with a comma";
                    break;
        case InvalidChar:       
                    cerr << "Invalid set character";
                    break;
        case MissingLeftBrace:  
                    cerr << "Missing left brace '{'";
                    break;
        case InvalidInputData:  
                    cerr << "Invalid input data element";
                    break;
        case EndOfFile:         
                    cerr << "Premature end of file";
                    break;
        case OutOfMemory:  
                    cerr << "Memory allocation failure";
                    break;
        case InvalidMemberRef:  
                    cerr << "Invalid member reference";
                    break;
        case SetsDifferentSize:  
                    cerr << "Sets are not the same size";
                    break;
    }
    cout << endl;
    exit(1);
}

// determine the index of the array element
// containing the bit representing elt
template <class T>
int Set<T>::ArrayIndex(const T& elt) const
{
    // convert elt to int and shift
    return int(elt) >> 4;
}

// create an unsigned short value with a 1 in the
// bit position of elt
template <class T>
unsigned short Set<T>::BitMask(const T& elt) const
{
    // use & to find remainder after dividing by
    // 16. 0 stays in right-most bit, 15 goes on far left
    return 1 << (int(elt) & 15);
}

// constructor. create an empty set
template <class T>
Set<T>::Set(int sz): setrange(sz)
{
    // number of unsigned shorts needed to hold set elements
    arraysize = (setrange+15) >> 4;
    
    // allocate the array
    member = new unsigned short [arraysize];
    if (member == NULL)
        Error(OutOfMemory);
        
    // create an empty set by setting all bits to 0
    for (int i = 0; i < arraysize; i++)
        member[i] = 0;
}

template <class T>
Set<T>::Set(const Set<T>& x)
{
    setrange = x.setrange;
    arraysize = x.arraysize;
    
    // allocate the array
    member = new unsigned short [arraysize];
    if (member == NULL)
        Error(OutOfMemory);
        
    // copy set elements from x
    for (int i = 0; i < arraysize; i++)
        member[i] = x.member[i];
}

template <class T>
Set<T>::~Set(void)
{
    delete [] member;
}

template <class T>
Set<T>& Set<T>::operator= (const Set<T>& rhs)
{
    if (setrange != rhs.setrange)
        Error(SetsDifferentSize);
        
    // copy set elements from rhs
    for (int i = 0; i < arraysize; i++)
        member[i] = rhs.member[i];
    return *this;
}

// determine whether elt is in the set
template <class T>
int Set<T>::IsMember(const T& elt)
{
    // is int(elt) in range 0 to setrange-1 ?
    if (int(elt) < 0 || int(elt) >= setrange)
        Error(InvalidMemberRef);

	// return the bit corresponding to elt
    return member[ArrayIndex(elt)] & BitMask(elt);
}

// determine if the current set and x are equal
template <class T>
int Set<T>::operator== (const Set<T>& x) const
{
	int retval = 1;
	
	// the sets must have the same range
    if (setrange != x.setrange)
        Error(SetsDifferentSize);

	for(int i=0;i < arraysize;i++)
		if (member[i] != x.member[i])
		{
			retval = 0;
			break;
		}
	return retval;
}

// form and return the union of the current Set
// object and object x
template <class T>
Set<T> Set<T>::operator+ (const Set<T>& x) const
{
	// the sets must have the same range
    if (setrange != x.setrange)
        Error(SetsDifferentSize);
        
	// form the union in tmp
    Set<T> tmp(setrange);

	// each array element of tmp is the bitwise
	// OR of the current object and x
    for (int i = 0; i < arraysize; i++)
        tmp.member[i] = member[i] | x.member[i];
        
    // return the union
    return tmp;
}

template <class T>
Set<T> Set<T>::operator* (const Set<T>& x) const
{
	// the sets must have the same range
    if (setrange != x.setrange)
        Error(SetsDifferentSize);
        
	// form the intersection in tmp
    Set<T> tmp(setrange);

	// each array element of tmp is the bitwise
	// AND of the current object and x
    for (int i = 0; i < arraysize; i++)
        tmp.member[i] = member[i] & x.member[i];
        
    // return the intersection
    return tmp;
}

// insert elt into the set
template <class T>
void Set<T>::Insert(const T& elt)
{
    // is int(elt) in range 0 to setrange-1 ?
    if (int(elt) < 0 || int(elt) >= setrange)
        Error(InvalidMemberRef);

    // set bit corresponding to elt
    member[ArrayIndex(elt)] |= BitMask(elt);
}

// delete elt from the set
template <class T>
void Set<T>::Delete(const T& elt)
{
    // is int(elt) in range 0 to setrange-1 ?
    if (int(elt) < 0 || int(elt) >= setrange)
        Error(InvalidMemberRef);

    // clear the bit corresponding to elt. note
    // that ~BitMask(elt) has a 0 in the bit
    // we are interested in an 1 in all others
    member[ArrayIndex(elt)] &= ~BitMask(elt);
}

template <class T>
istream& operator>> (istream& istr, Set<T>& x)
{
    char c;
    int haveComma = 0, needComma = 0;
    T elt;
    int i;

    for (i = 0; i < x.arraysize; i++)
        x.member[i] = 0;

    // skip leading white space
    c = ' ';
    while (c == ' ' || c == '\t' || c == '\n')
        if (istr.get(c) == 0)
            x.Error(EndOfFile);
    if (c != '{')
        x.Error(MissingLeftBrace);

    if (istr.get(c) == 0)
        x.Error(EndOfFile);
        
    while (c != '}')
    {
        switch(c)
        {
            case ' ':
            case '\t':                  
            case '\n':  break;
        
            case '{':   x.Error(ExpectRightBrace);
                        break;
        
            case ',':   if (haveComma == 1)
                            x.Error(MissingValue);
                        else
                        {
                            haveComma = 1;
                            needComma = 0;
                        }
                        break;
        
            default:
                        if (needComma)
                            x.Error(MissingComma);
                        istr.putback(c);
                        if(istr >> elt == 0)
                            x.Error(InvalidInputData);
                        if (int(elt) < 0 ||
                            int(elt) >= x.setrange)
                                x.Error(InvalidInputData);
                        x.member[x.ArrayIndex(elt)]
                                        |= x.BitMask(elt);
                        needComma = 1;
                        haveComma = 0;
                        break;
        }
        if (istr.get(c) == 0)
            x.Error(EndOfFile);
    }
    if (haveComma == 1)
        x.Error(MissingValue);
    return istr;
}

template <class T>
ostream& operator<< (ostream& ostr, const Set<T>& x)
{
    int i, j, setElt;
    int needComma = 0;
    T elt;
    
    ostr << "{";

    for (setElt = 0; setElt < x.setrange; setElt++)
    {
    if (x.member[x.ArrayIndex(T(setElt))] &
        x.BitMask(T(setElt)))
        {
            elt = T(setElt);
           if (needComma == 1)
                ostr << ", " << elt;
            else
            {
                ostr << elt;
                needComma = 1;
            }
        }
    }
    ostr << "}  ";
    return ostr;
}

#endif  // SET_CLASS
