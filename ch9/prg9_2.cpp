#include <iostream.h>
#pragma hdrstop

#include "random.h"
#include "strclass.h"
#include "nodelib.h"

void main(void)
{

    // node list to hold jumbled characters
    Node<char> *jumbleword = NULL;

    // input string, random number generator, counters
    String  s;
    RandomNumber rnd;
    int i, j;
    
    // input four strings
    for (i = 0; i < 4; i++)
    {
        cin >> s;
        // use Random(2) to determine if char moves to
        // front (value = 0) or rear (value = 1) of list
        for (j = 0; j < s.Length(); j++)
            if (rnd.Random(2))
                InsertRear(jumbleword, s[j]);
            else
                InsertFront(jumbleword, s[j]);

        // print the input string and its jumbled variation
        cout << "String/Jumble: " << s << "   ";
        PrintList(jumbleword);
        cout << endl << endl;
        ClearList(jumbleword);
    }
 }

/*      
<Run of Program 9.2>

pepper
String/Jumble: pepper   r  p  p  e  p  e

hawaii
String/Jumble: hawaii   i  i  h  a  w  a

jumble
String/Jumble: jumble   e  b  m  j  u  l

C++
String/Jumble: C++   +  C  +
*/
