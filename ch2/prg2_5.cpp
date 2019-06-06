#include <iostream.h>
#include <fstream.h>
#include <string.h>     // must include if string functions used
#include <ctype.h>      // provides isalpha and isdigit
#include <stdlib.h>

// declare the word structure
struct KeyWord
{
	char keyword[20];
	int  count;
};

// declare and initialize the table of keywords
KeyWord KeyWordTable[] =
{
    {"else", 0}, {"for", 0},{"if", 0},{"include", 0},{"while", 0}
};

// the sequential search algorithm on the array of keywords
int SeqSearch(KeyWord *tab, int n, char *word) 
{
    int i;

    // scan list. compare word with keyword in current record 
    for (i=0; i < n; i++, tab++)
	if (strcmp(word, tab->keyword) == 0)   
	    return i;                   // return index if match
    return -1;                          // sorry, no match
}

// extract a word beginning with a letter and possibly
// other letters/digits
int GetWord (ifstream& fin, char w[])
{
    char c;
    int  i = 0;

    // skip non-alphabetic input
    while ( fin.get(c) && !isalpha(c))
	;
	
    // return 0 (Failure) on end of file
    if (fin.eof())
	return 0;
    
    // record 1st letter of the word    
    w[i++] = c;
    
    // collect letters and digits and NULL terminate string
    while (fin.get(c) && (isalpha(c) || isdigit(c)))
	w[i++] = c;
    w[i] = '\0';
    
    return  1;              // return 1 (Success)
}
    
void main(void)
{
    const int MAXWORD = 50;             // max size of any word
    
    // declare the table size and initialize its value
    const int NKEYWORDS = sizeof(KeyWordTable)/sizeof(KeyWord);
    
    int n;
    char word[MAXWORD], c;
    ifstream fin;

    // open file with error checking    
    fin.open("prg2_5.cpp",ios::in | ios::nocreate);
    if (!fin)
    {
	cerr << "Could not open file 'prg2_5.cpp'" << endl;
	exit (1);
    }
    
    // extract words until end of file
    while (GetWord(fin, word))
	// if a match in keyword table, increment count
	if ((n = SeqSearch(KeyWordTable,NKEYWORDS,word)) != -1)
		KeyWordTable[n].count++;
    
    // scan the keyword table and print record fields 
    for (n = 0; n < NKEYWORDS; n++)
	if (KeyWordTable[n].count > 0)
	{
	    cout << KeyWordTable[n].count;
	    cout << "  " << KeyWordTable[n].keyword << endl;
	}
    fin.close();
}
/*
<Run of Program 2.5>

1  else
3  for
9  if
7  include
4  while
*/

