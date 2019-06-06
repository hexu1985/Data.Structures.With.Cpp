#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "strclass.h"
#include "search.h"    // include BinSearch

void main(void)
{
    // we search an array of ordered strings from stream fin
    String wordlist[50];
    ifstream    fin;
    
    String word;
    int pos, i;

    // open file "vocab.dat" containing alphabetized words
    fin.open("vocab.dat");
    
    // read until end of file and initialize wordlist
    i = 0;
    while(fin >> wordlist[i])
        i++;
    
    // prompt for a word
    cout << "Enter a word: ";
    cin >> word;
    
    // use the binary search to look for the word
    if ((pos = BinSearch(wordlist,0,i,word)) != -1)
        cout << word << " is in the list at index " << pos << endl;
    else
        cout << word << " is not in the list." <<  endl;
}

/*
<Input file "vocab.dat">

array
class
file
struct
template
vector

<Run #1 of Program 10.2>
Enter a word: template
template is in the list at index 4

<Run #2 of Program 10.2>
Enter a word: mark
mark is not in the list.
*/
