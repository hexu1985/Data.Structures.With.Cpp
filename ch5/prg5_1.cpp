
#include <iostream.h>
#pragma hdrstop

typedef char DataType;  // stack elements are characters

#include "astack.h"

// creates a new string with all blank characters removed
void Deblank(char *s, char *t)
{
    // loop through expression until NULL character is found
    while(*s != NULL)
    {
        // if character is a non-blank, copy to new string
        if (*s != ' ')
            *t++ = *s;
        s++;            // move to next character
    }
    *t = NULL;          // append NULL to new string
}

void main(void)
{
    const int True = 1, False = 0;
    
    // stack S holds chars in reverse order
    Stack S;
    
    char palstring[80], deblankstring[80], c;
    int i = 0;
    int ispalindrome = True;    // assume string is a palindrome

    // read in the full-line string
    cin.getline(palstring,80,'\n');

    // remove blanks from string and put result in deblankstring
    Deblank(palstring,deblankstring);

    // push the chars of deblanked expression on the stack
    i = 0;
    while(deblankstring[i] != 0)
    {
        S.Push(deblankstring[i]);
        i++;
    }

    // now pop stack, comparing characters with original string
    i = 0;
    while (!S.StackEmpty())
    {
        c = S.Pop();    // get next character from  stack
        // if chars don't match, break out of the loop
        if (c != deblankstring[i])
        {
            ispalindrome = False;   // not a palindrome
            break;
        }
        i++;
    }

    if (ispalindrome)
        cout << '\"' << palstring << '\"' 
             << " is a palindrome" << endl;
    else
        cout << '\"' << palstring << '\"' 
             << " is not a palindrome" << endl;
}

/*
<Run #1 of Program 5.1>

madam im adam
"madam im adam" is a palindrome

<Run #2 of Program 5.1>

a man a plan a canal panama
"a man a plan a canal panama" is a palindrome

<Run #3 of Program 5.1>
palindrome
"palindrome" is not a palindrome
*/
