#ifndef STRING_CLASS
#define STRING_CLASS

#include <iostream.h>
#include <string.h>
#include <stdlib.h>

#ifndef NULL
const int NULL = 0;
#endif  // NULL

const int outOfMemory = 0, indexError = 1;

class String
{
    private:
        // pointer to dynamically allocated string. length
        // of the string includes the NULL character
        char *str;
        int  size;
        
        // error reporting function
        void Error(int errorType, int badIndex = 0) const;

    public:
        // constructors
        String(char *s = "");
        String(const String& s);
        
        // destructor
        ~String(void);
                
        // assignment operators
        // String = String, String = C++String
        String& operator= (const String& s);
        String& operator= (char *s);
        
        // relational operators
        // String==String,String==C++String,C++String==String
        int operator== (const String& s) const;
        int operator== (char *s) const;
        friend int operator== (char *str, const String& s);
        
        // String!=String,String!=C++String,C++String!=String
        int operator!= (const String& s) const;
        int operator!= (char *s) const;
        friend int operator!= (char *str, const String& s);
        
        // String<String,String<C++String,C++String<String
        int operator< (const String& s) const;
        int operator< (char *s) const;
        friend int operator< (char *str, const String& s);
        
        // String<=String,String<=C++String,C++String<=String
        int operator<= (const String& s) const;
        int operator<= (char *s) const;
        friend int operator<= (char *str, const String& s);
        
        // String>String,String>C++String,C++String>String
        int operator> (const String& s) const;
        int operator> (char *s) const;
        friend int operator> (char *str, const String& s);
        
        // String>=String,String>=C++String,C++String>=String
        int operator>= (const String& s) const;
        int operator>= (char *s) const;
        friend int operator>= (char *str, const String& s);

        // String concatenation operators
        // String+String, String+C++String, C++String+String
        // String += String, String += C++String
        String operator+ (const String& s) const;   
        String operator+ (char *s) const;
        friend String operator+ (char *str,const String& s);
        void operator+= (const String& s);
        void operator+= (char *s);

        // String functions
        // beginning at index start, find c
        int Find(char c, int start) const;
        // find last occurrence of c
        int FindLast(char c) const;
        // extract a substring
        String Substr(int index, int count) const;
        // insert a String into String
        void Insert(const String& s, int index);
        // insert a C++String into String
        void Insert(char *s, int index);
        // delete a substring
        void Remove(int index, int count);

        // String indexing
        char& operator[] (int n);
        
        // convert String to C++String
        operator char* (void) const;
        
        // String I/O
        friend ostream& operator<< (ostream& ostr,
                                    const String& s);
        friend istream& operator>> (istream& istr,
                                    String& s);
		// read characters up to delimiter
        int ReadString(istream& is=cin,
					   char delimiter='\n');

        // additional methods
        int Length(void) const;
        int IsEmpty(void) const;
        void Clear(void);
};

void String::Error(int errorType, int badIndex) const
{
    if (errorType == outOfMemory)
        cerr << "Memory exhausted!" << endl;
    else
        cerr << "Index " << badIndex
             << " out of range" << endl;
    exit(1);
}

// constructor. allocate memory and copy in a C++String
String::String(char *s)
{
    // length includes the NULL character
    size = strlen(s) + 1;
    
    // make room for string and NULL char and copy s.
    str = new char [size];
    // terminate program if memory is exhausted.
    if (str == NULL)
        Error(outOfMemory);
    strcpy(str,s);
}

// copy constructor
String::String(const String& s)
{
    // current object as length of s
    size = s.size;
    
    // allocate same amount of space as s uses. copy string
    str = new char [size];
    if (str == NULL)
        Error(outOfMemory);
    strcpy(str,s.str);
}

// destructor
String::~String(void)
{
    delete [] str;
}

// assignment operator. String to String
String& String::operator= (const String& s)
{
    // if sizes differ, delete current string and reallocate
    if (s.size != size)
    {
        delete [] str;
        str = new char [s.size];
        if(str == NULL)
            Error(outOfMemory);
        // assign size to be size of s
        size = s.size;
    }
    
    // copy s.str and return reference to current object
    strcpy(str,s.str);
    return *this;
}

// assignment operator. C++String to String
String& String::operator= (char *s)
{
    int slen = strlen(s) + 1;
    
    // if sizes differ, delete current string and reallocate
    if (slen != size)
    {
        delete [] str;
        str = new char [slen];
        if (str == NULL)
            Error(outOfMemory);
        size = slen;
    }
    // copy s and return reference to current object
    strcpy(str,s);
    return *this;
}
// all relational operators use C++ string function strcmp

// String == String
int String::operator== (const String& s) const
{
    return strcmp(str,s.str) == 0;
}

// String == C++String
int String::operator== (char *s) const
{
    return strcmp(str,s) == 0;
}

// C++String == String. this is a friend function, since
// the left operand is a C++String.
int operator== (char *str, const String& s)
{
    return strcmp(str,s.str) == 0;
}

// String != String
int String::operator!= (const String& s) const
{
    return strcmp(str,s.str) != 0;
}

// String != C++String
int String::operator!= (char *s) const
{
    return strcmp(str,s) != 0;
}

// C++String != String
int operator!= (char *str, const String& s)
{
    return strcmp(str,s.str) != 0;
}

// String < String
int String::operator< (const String& s) const
{
    return strcmp(str,s.str) < 0;
}

// String < C++String
int String::operator< (char *s) const
{
    return strcmp(str,s) < 0;
}

// C++String < String
int operator< (char *str, const String& s)
{
    return strcmp(str,s.str) < 0;
}

// String <= String
int String::operator<= (const String& s) const
{
    return strcmp(str,s.str) <= 0;
}

// String <= C++String
int String::operator<= (char *s) const
{
    return strcmp(str,s) <= 0;
}

// C++String <= String
int operator<= (char *str, const String& s)
{
    return strcmp(str,s.str) <= 0;
}

// String > String
int String::operator> (const String& s) const
{
    return strcmp(str,s.str) > 0;
}

// String > C++String
int String::operator> (char *s) const
{
    return strcmp(str,s) > 0;
}

// C++String > String
int operator> (char *str, const String& s)
{
    return strcmp(str,s.str) > 0;
}

// String >= String
int String::operator>= (const String& s) const
{
    return strcmp(str,s.str) >= 0;
}

// String >= C++String
int String::operator>= (char *s) const
{
    return strcmp(str,s) >= 0;
}

// C++String >= String
int operator>= (char *str, const String& s)
{
    return strcmp(str,s.str) >= 0;
}

// concatention: String + String
String String::operator+ (const String& s) const
{
    // build the new string with length len in temp
    String temp;
    int len;
    
    // delete the NULL string created when temp declared
    delete [] temp.str;
    
    // compute length of concatenated string and allocate
    // memory in temp
    len = size + s.size - 1;    // only one NULL terminator
    temp.str = new char [len];
    if (temp.str == NULL)   
        Error(outOfMemory);

    // assign concatenated string size and build string
    temp.size = len;
    strcpy(temp.str,str);       // copy str to temp
    strcat(temp.str, s.str);    // concatenate s.str
    return temp;                // return temp
}

// concatention: String + C++String. same algorithm as
// String + String, with a C++String as the right operand
String String::operator+ (char *s) const
{
    String temp;
    int len;
    
    delete [] temp.str;
    
    len = size + strlen(s);
    temp.str = new char [len];
    if (temp.str == NULL)   
        Error(outOfMemory);
        
    temp.size = len;
    strcpy(temp.str,str);
    strcat(temp.str, s);
    return temp;
}

// concatention: C++String + String. same algorithm as
// String + String, with a C++String as the left operand
String operator+ (char *cs, const String& s)
{
    String temp;
    int len;
    
    delete [] temp.str;
    
    len = strlen(cs) + s.size;
    temp.str = new char [len];
    if (temp.str == NULL)   
        s.Error(outOfMemory);
        
    temp.size = len;
    strcpy(temp.str,cs);
    strcat(temp.str, s.str);
    return temp;
}

// concatenate and assign: String += String
// the current object is modified
void String::operator+= (const String& s)
{
    // allocate new dynamic memory for current object
    char *tempstr;
    int len;

    // compute length of concatenated string and allocate
    // memory in tempstr
    len = size + s.size - 1;
    tempstr = new char [len];
    if (tempstr == NULL)    
        Error(outOfMemory);
        
    // copy string to tempstr and concatenate s.str
    strcpy(tempstr,str);
    strcat(tempstr, s.str);
    
    // delete current string
    delete [] str;
    
    // new string has address tempstr with new length len
    str = tempstr;
    size = len;
}

void String::operator+= (char *s)
{
    int len;
    char *tempstr;

    len = size + strlen(s);
    tempstr = new char [len];
    if (tempstr == NULL)    
        Error(outOfMemory);
    strcpy(tempstr,str);
    strcat(tempstr, s);
    delete [] str;
    str = tempstr;
    size = len;
}

int String::Find(char c, int start) const
{
    int ret;
    char *p;
    
    p = strchr(&str[start],c);
    if (p != NULL)
        ret = int(p-str);
    else
        ret = -1;
    return ret;
}

// return index of last occurrence of c in string
int String::FindLast(char c) const
{
    int ret;
    char *p;
    
    // use C++ library function strrchr. returns pointer to
    // the last occurrence of a character in the string
    p = strrchr(str,c);
    if (p != NULL)
        ret = int(p-str);   // compute index
    else
        ret = -1;           // return -1 on failure
    return ret;
}

// return substring starting at index for count characters
String String::Substr(int index, int count) const
{
    // number of characters from index to end of string
    int charsLeft = size-index-1,i;
    
    // build substring in temp
    String temp;
    char *p, *q;
    
    // return null string if index too large
    if (index >= size-1)
        return temp;
        
    // if count > remaining chars, use remaining chars
    if (count > charsLeft)
        count = charsLeft;
        
    // delete the NULL string created when temp declared
    delete [] temp.str;
    
    // allocate dynamic memory for the substring
    temp.str = new char [count+1];
    if (temp.str == NULL)
        Error(outOfMemory);
        
    // copy count chars from str to temp.str
    for(i=0,p=temp.str,q=&str[index];i < count;i++)
        *p++ = *q++;
    // NULL terminate
    *p = 0;
    
    temp.size = count+1;
    return temp;
}

void String::Insert(const String& s, int index)
{
    int newsize, length_s = s.size-1, i;
    char *newstr, *p, *q;
    
    newsize = size + length_s;
    newstr = new char [newsize];
    if (newstr == NULL)
        Error(outOfMemory);
    for(i=0,p = newstr, q = str;i <= index-1;i++)
        *p++ = *q++;
    strcpy(p,s.str);
    p += length_s;
    strcpy(p,&str[index]);
    delete [] str;  // delete old string
    size = newsize; // new string size
    str = newstr;   // new string pointer
}

void String::Insert(char *s, int index)
{
    int newsize, length_s = strlen(s), i;
    char *newstr, *p, *q;
    
    newsize = size + length_s;
    newstr = new char [newsize];
    if (newstr == NULL)
        Error(outOfMemory);
    for(i=0,p = newstr, q = str;i <= index-1;i++)
        *p++ = *q++;
    strcpy(p,s);
    p += length_s;
    strcpy(p,&str[index]);
    delete [] str;  // delete old string
    size = newsize; // new string size
    str = newstr;   // new string pointer
}

void String::Remove(int index, int count)
{
    int charsLeft = size-index-1, newsize, i;
    char *newstr, *p, *q;
    
    if (index >= size-1)
        return;             // return if index too large
    // if count > remaining chars, just use remaining chars
    if (count > charsLeft)
        count = charsLeft;
    newsize = size - count;
    newstr = new char [newsize];
    if (newstr == NULL)
        Error(outOfMemory);
    for(i=0,p=newstr,q=str;i <= index-1;i++)
        *p++ = *q++;
    q += count;
    strcpy(p,q);
    delete [] str;
    size = newsize;
    str = newstr;
}

// String index operator
char& String::operator[] (int n)
{
    if (n <0 || n >= size-1)
        Error(indexError,n);
    return str[n];
}

// pointer conversion operator
String::operator char* (void) const
{
    return str;
}

istream& operator>> (istream& istr, String& s)
{
    char tmp[256];
    
    if (istr >> tmp)                // eof?
    {
        delete [] s.str;            // delete existing string
        s.size = strlen(tmp) + 1;
        s.str = new char [s.size];
        if (s.str == NULL)
            s.Error(outOfMemory);
        strcpy(s.str,tmp);
    }
    return istr;
}

ostream& operator<< (ostream& ostr, const String& s)
{
    ostr << s.str;
    return ostr;
}

// read characters from istr up to delimiter
// replace delimiter by the NULL character.
// NOTE: With Symantec C++, use delimiter='\n' to
// input a line from cin and delimiter='\r' to input a
// a line from a text file.
int String::ReadString (istream& istr, char delimiter)
{
    // read line into tmp
    char tmp[256];

    // if not eof, read line of up to 255 characters
    if (istr.getline(tmp, 256, delimiter))
    {
        // delete string and allocate memory for new one
        delete [] str;
        size = strlen(tmp) + 1;
        str = new char [size];
        if (str == NULL)
            Error(outOfMemory);
            
        // copy tmp. return number of chars read
        strcpy(str,tmp);
        return size-1;
    }
    else
        return -1;  // return -1 on end of file
}

int String::Length(void) const
{
    return size-1;
}

int String::IsEmpty(void) const
{
    return size == 1;
}

void String::Clear(void)
{
    delete [] str;
    size = 1;
    
    str = new char [size];  // allocate space for NULL char
    if (str == NULL)
        Error(outOfMemory);
    str[0] = 0;
}

#endif  // STRING_CLASS
