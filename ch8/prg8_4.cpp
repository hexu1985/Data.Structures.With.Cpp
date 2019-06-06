#include <iostream.h>
#pragma hdrstop

#include "strclass.h"

#define TF(b)   ((b) ? "TRUE" : "FALSE")

void main(void)
{
    String s1("STRING "), s2("CLASS");
    String s3;
    int i;
    char c, cstr[30];
    
    s3 = s1 + s2;
    cout << s1 << "concatenated with " << s2 << " = "
         << s3 << endl;
    cout << "Length of " << s2 << " = " << s2.Length() << endl;
    cout << "The first occurrence of 'S' in " << s2 << " =  " <<
            s2.Find('S',0) << endl;
    cout << "The last occurrence of 'S' in " << s2 << " is " <<
            s2.FindLast('S') << endl;
    cout << "Insert 'OBJECT ' into s3 at position 7." << endl;
    s3.Insert("OBJECT ",7);
    cout << s3 << endl;
    
    
    s1 = "FILE1.S";
    for(i=0;i < s1.Length();i++)
    {
        c = s1[i];
        if (c >= 'A' && c <= 'Z')
        {
            c += 32;    // convert c to lower case
            s1[i] = c;
        }
    }
    cout << "The string 'FILE1.S' converted to lower case is ";
    cout << s1 << endl;
    
    cout << "Test relational operators with strings ";
    cout << "s1 = 'ABCDE'  s2 = 'BCF'" << endl;
    
    s1 = "ABCDE";
    s2 = "BCF";
    
    cout << "s1 < s2  is " << TF(s1 < s2) << endl;
    cout << "s1 == s2  is " << TF(s1 == s2) << endl;
    
    cout << "Use 'operator char* ()' to get s1"
            " as a C++ string: ";
    strcpy(cstr,s1);
    cout << cstr << endl;
}

/*
<Run of Program 8.4>

STRING concatenated with CLASS = STRING CLASS
Length of CLASS = 5
The first occurrence of 'S' in CLASS =  3
The last occurrence of 'S' in CLASS is 4
Insert 'OBJECT ' into s3 at position 7.
STRING OBJECT CLASS
The string 'FILE1.S' converted to lower case is file1.s
Test relational operators with strings s1 = 'ABCDE'  s2 = 'BCF'
s1 < s2  is TRUE
s1 == s2  is FALSE
Use 'operator char* ()' to get s1 as a C++ string: ABCDE
*/
